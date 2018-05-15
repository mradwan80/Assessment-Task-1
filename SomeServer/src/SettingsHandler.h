
#ifndef Settings_H
#define Settings_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Geometry.h"
#include <memory>
using namespace std;

class AppSettings
{
public:
	static string address;
	static string S3Bucket;
	static int ObjectsNum;
	static Point3D P1, P2;
	

	static void ReadSettings(string filename);

};
string AppSettings::address;
string AppSettings::S3Bucket;
int AppSettings::ObjectsNum;
Point3D AppSettings::P1;
Point3D AppSettings::P2;

void AppSettings::ReadSettings(string filename)
{
	string line;
	stringstream strline;
	string name;
	string value;
	char delim1 = ':';
	char delim2 = '\n';

	ifstream input;
	input.open(filename);

	getline(input, name, delim1);
	while (!input.eof())
	{
		getline(input, value, delim2);

		if (name.compare("address") == 0)
		{
			address = value;
		}
		else if (name.compare("bucket") == 0)
		{
			S3Bucket = value;
		}
		else if (name.compare("objects_num") == 0)
		{
			int i;
			stringstream stream;
			stream << value;
			stream >> i;
			ObjectsNum = i;
		}
		else if (name.compare("point_1_x") == 0)
		{
			float f;
			stringstream stream;
			stream << value;
			stream >> f;
			P1.fillX(f);
		}
		else if (name.compare("point_1_y") == 0)
		{
			float f;
			stringstream stream;
			stream << value;
			stream >> f;
			P1.fillY(f);
		}
		else if (name.compare("point_1_z") == 0)
		{
			float f;
			stringstream stream;
			stream << value;
			stream >> f;
			P1.fillZ(f);
		}
		else if (name.compare("point_2_x") == 0)
		{
			float f;
			stringstream stream;
			stream << value;
			stream >> f;
			P2.fillX(f);
		}
		else if (name.compare("point_2_y") == 0)
		{
			float f;
			stringstream stream;
			stream << value;
			stream >> f;
			P2.fillY(f);
		}
		else if (name.compare("point_2_z") == 0)
		{
			float f;
			stringstream stream;
			stream << value;
			stream >> f;
			P2.fillZ(f);
		}



		getline(input, name, delim1);
	}
	input.close();

}

#endif