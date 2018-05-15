#include <gtest\gtest.h>
#include <SomeServer\src\Geometry.h>
#include <SomeServer\src\main.h>
#include <SomeServer\src\SettingsHandler.h>

using namespace std;
TEST(Interpolation, TestInterpolation)
{
	Point3D p1(1.0, 1.0, 1.0);
	Point3D p2(3.0, 3.0, 3.0);
	vector<Point3D> arr = GetObjectsCoordinates(p1, p2, 3);
		
	EXPECT_EQ(arr[1].X(), 2.0);
	EXPECT_EQ(arr[1].Y(), 2.0);
	EXPECT_EQ(arr[1].Z(), 2.0);
	
}

TEST(ConfigValues, TestConfigValues)
{
	AppSettings::ReadSettings("..\\SomeServer\\settings.ini");
	EXPECT_GT(AppSettings::ObjectsNum, 0);

}