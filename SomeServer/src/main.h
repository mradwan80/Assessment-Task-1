#ifndef Main_H
#define Main_H

#include <memory>
#include <cstdlib>
#include <restbed>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/core/Aws.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h> 
#include <json\json.h>
#include <iostream>
#include <fstream>
#include "Geometry.h"
#include "SettingsHandler.h"
using namespace std;
using namespace restbed;
using namespace Aws::S3;
using namespace Aws::S3::Model;


void Post_method_handler(const shared_ptr< Session > session);
void Get_method_handler(const shared_ptr< Session > session);

/*
returns a list of keys of the files in the s3 bucket
input: none
output: a list of keys
*/
Aws::Vector<Aws::S3::Model::Object> GetListOfBucketKeys(bool& success)
{
	//initialize the API//
	Aws::SDKOptions options;
	Aws::InitAPI(options);


	//define the configurations (necessary for connecting to the bucket)//
	Aws::Client::ClientConfiguration clientConfig;
	clientConfig.scheme = Aws::Http::Scheme::HTTPS;
	clientConfig.region = Aws::Region::EU_CENTRAL_1;
	clientConfig.connectTimeoutMs = 30000;
	clientConfig.requestTimeoutMs = 600000;

	//definde the client and request, and get the keys//
	Aws::S3::S3Client s3_client(clientConfig);
	Aws::S3::Model::ListObjectsRequest objects_request;
	objects_request.WithBucket(AppSettings::S3Bucket.c_str());
	auto list_objects_outcome = s3_client.ListObjects(objects_request);


	//return a vector if retrieval is successful//
	if (list_objects_outcome.IsSuccess())
	{
		success = true;

		//get keys in an AWS::Vector object
		Aws::Vector<Aws::S3::Model::Object> object_list = list_objects_outcome.GetResult().GetContents();

		//shut down and return//
		Aws::ShutdownAPI(options);
		return object_list;

	}
	else
	{
		success = false;
		Aws::ShutdownAPI(options);
		return Aws::Vector<Aws::S3::Model::Object>();

	}


}

/*
interpolates the positions of the objects, based on positions of first and last objects
input: P1,P2,ObjectsNum
output: a vector of interpolated positions
*/
vector<Point3D> GetObjectsCoordinates(Point3D P1, Point3D P2, int ObjectsNum)
{
	vector<Point3D>Coordinates(ObjectsNum);

	Point3D step;
	step = (P2 - P1) / (ObjectsNum - 1);		//calculate the incrementing step//

	Coordinates[0] = P1;						//position of first point is already given//
	for (int p = 1; p < ObjectsNum - 1; p++)
	{
		Coordinates[p] = Coordinates[p - 1] + step;		//increement by step//
	}
	Coordinates[ObjectsNum - 1] = P2;			//position of last point is already given//

	return Coordinates;

}

/*
converts the positions and urls of the objects into a json string
input:  objects list and positions array
output: json string

json string format: { "ObjectsNum":- , "ObjesctsArray": [{"url":"-","x":-,"y":-,"z":-},...]} }
*/
string ConvertToJsonFormat(Aws::Vector<Aws::S3::Model::Object> object_list, vector<Point3D> Coordinates)
{
	Json::Value jstruct;
	Json::Value arr;
	Json::Value root;

	string key;

	root["ObjectsNum"] = Coordinates.size();	//first attribute//

													//loop to fill the array (url, x, y, z)
	for (int ob = 0; ob < Coordinates.size(); ob++)
	{
		key.assign(object_list[ob].GetKey().data(), object_list[ob].GetKey().size());	//convert the key into string//

		jstruct["URL"] = "S3/" + AppSettings::S3Bucket + '/' + key;
		jstruct["x"] = Coordinates[ob].X();
		jstruct["y"] = Coordinates[ob].Y();
		jstruct["z"] = Coordinates[ob].Z();

		arr.append(jstruct);
	}

	root["ObjectsArray"] = arr;					//second attribute//

	Json::StreamWriterBuilder builder;
	builder["indentation"] = "";
	string s = Json::writeString(builder, root);	//convert json object root to string//

	return s;

}


#endif