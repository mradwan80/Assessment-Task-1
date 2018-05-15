#include "main.h"


/*
sends back a response with a json object containing objects URLs and positions
input: session
output: none
*/
void Post_method_handler(const shared_ptr< Session > session)
{
	fprintf(stdout, "Entered the handler\n");

	const auto request = session->get_request();

	int content_length = request->get_header("Content-Length", 0);

	bool success;
	Aws::Vector<Aws::S3::Model::Object> object_list = GetListOfBucketKeys(success);

	if (object_list.size() > 0 && success)
	{
		//BucketObjectsNum holds the final number of objects to be sent.//
		//In case the bucket contains less than the number required in the config file, then BucketObjectsNum = bucket objects//
		int ReturnedObjectsNum = AppSettings::ObjectsNum;
		if (object_list.size() < AppSettings::ObjectsNum)
			ReturnedObjectsNum = object_list.size();

		//get coordinates array. Note that the size of the returned Coordinates is ReturnedObjectsNum//
		vector<Point3D>Coordinates = GetObjectsCoordinates(AppSettings::P1, AppSettings::P2, ReturnedObjectsNum);

	
		//convert array into json//
		string s = ConvertToJsonFormat(object_list, Coordinates);

		//printf(s.c_str());	printf("\n");

		//send json string//
		session->fetch(content_length, [s](const shared_ptr< Session > session, const Bytes & body)
		{
			fprintf(stdout, "%.*s\n", (int)body.size(), body.data());
			session->close(OK, s, { { "Content-Length", std::to_string(s.size()) },{ "Content-Type", "application/json" } });
		});
	}
	else if(!success)	//couldn't access s3//
	{
		session->fetch(content_length, [](const shared_ptr< Session > session, const Bytes & body)
		{
			string s = "Accessing repository failed";
			fprintf(stdout, "%.*s\n", (int)body.size(), body.data());
			session->close(BAD_REQUEST, s, { { "Content-Length", std::to_string(s.size()) },{ "Content-Type", "text/html" } });

		});
	}
	else	//object_list.size()==0//
	{
		session->fetch(content_length, [](const shared_ptr< Session > session, const Bytes & body)
		{
			string s = "No objects in repository";
			fprintf(stdout, "%.*s\n", (int)body.size(), body.data());
			session->close(BAD_REQUEST, s, { { "Content-Length", std::to_string(s.size()) },{ "Content-Type", "text/html" } });

		});
	}
	
}


void Get_method_handler(const shared_ptr< Session > session)
{
	Post_method_handler(session);
}

int main(const int, const char**)
{
	fprintf(stdout, "started\n");

	AppSettings::ReadSettings("settings.ini");					

	auto resource = make_shared< Resource >();							//define resource//
	resource->set_path("/resource");
	
	resource->set_method_handler("POST", Post_method_handler);			//both POST and GET are handled equivalently//
	resource->set_method_handler("GET", Get_method_handler);

	auto settings = make_shared< Settings >();							//set address and port//
	settings->set_bind_address(AppSettings::address);
	settings->set_port(1984);
	
	Service service;
	service.publish(resource);											//wait for requests//
	service.start(settings);

	return EXIT_SUCCESS;
}

