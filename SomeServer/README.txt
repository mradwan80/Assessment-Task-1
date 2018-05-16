

Dependencies:
restbed https://github.com/corvusoft/restbed
aws-sdk-cpp https://github.com/aws/aws-sdk-cpp
jsoncpp	https://github.com/open-source-parsers/jsoncpp


Notes:

1-command line:
g++ -std=c++11 -g -I"(aws-sdk-cpp folder)/aws-cpp-sdk-core/include" -I"(aws-sdk-cpp folder)/aws-cpp-sdk-s3/include" -I"(restbed folder)/distribution/include" -I"(jsoncpp folder)/include" main.cpp main.h Geometry.h SettingsHandler.h -o ObjectsServer -L"(aws-sdk-cpp build folder)/aws-cpp-sdk-core/" -L"(aws-sdk-cpp build folder)/aws-cpp-sdk-s3/" -L"(restbed folder)/distribution/library" -L"(json build folder)/debug/src/lib_json" -laws-cpp-sdk-core -laws-cpp-sdk-s3 -lrestbed -ljsoncpp

2-for linux:

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:(restbed folder)/distribution/library:(aws-sdk-cpp build folder)/aws-cpp-sdk-core:(aws-sdk-cpp build folder)/aws-cpp-sdk-s3:(json build folder)/debug/src/lib_json

3-for windows, add the following preprocessor definitions: USE_IMPORT_EXPORT;USE_WINDOWS_DLL_SEMANTICS;