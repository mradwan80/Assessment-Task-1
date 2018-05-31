# This file contains an executable only. No building, just run.

# get Ubuntu
FROM ubuntu:latest


# install the required depencies and building tools
RUN apt-get update
RUN apt-get install -y git
RUN apt-get update -y && apt-get install -y --no-install-recommends g++ make cmake pkg-config build-essential zlib1g-dev 
RUN apt-get update -y && apt-get install -y --no-install-recommends libcurl4-openssl-dev libssl-dev uuid-dev libpulse-dev libssl1.1

RUN git clone --recursive https://github.com/corvusoft/restbed.git
RUN mkdir restbed/build
WORKDIR restbed/build
RUN cmake -DBUILD_SSL=NO ..
RUN make install
RUN make test

WORKDIR /

RUN git clone --recursive https://github.com/open-source-parsers/jsoncpp.git
RUN mkdir jsoncpp/build
RUN mkdir jsoncpp/build/debug
WORKDIR jsoncpp/build/debug
RUN cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DARCHIVE_INSTALL_DIR=. -G "Unix Makefiles" ../..
RUN make

WORKDIR /

#get and build aws libraries
RUN git clone --recursive https://github.com/aws/aws-sdk-cpp
RUN mkdir aws-sdk-cpp/aws-cpp-sdk-core/build
WORKDIR aws-sdk-cpp/aws-cpp-sdk-core/build
RUN cmake -DBUILD_ONLY="core" /aws-sdk-cpp
RUN make
WORKDIR /
RUN mkdir aws-sdk-cpp/aws-cpp-sdk-s3/build
WORKDIR aws-sdk-cpp/aws-cpp-sdk-s3/build
RUN cmake -DBUILD_ONLY="s3" -Wno-noexcept-type  -DCPP_STANDARD=17 /aws-sdk-cpp
RUN make

WORKDIR /

RUN mkdir /home/ObjectsServer/
COPY . /home/ObjectsServer
WORKDIR /home/ObjectsServer


# build
RUN g++ -std=c++11 -g -I"/aws-sdk-cpp/aws-cpp-sdk-core/include" -I"/aws-sdk-cpp/aws-cpp-sdk-s3/include" -I"/restbed/distribution/include" -I"/jsoncpp/include" main.cpp main.h Geometry.h SettingsHandler.h -o ObjectsServer -L"/aws-sdk-cpp/aws-cpp-sdk-core/build/aws-cpp-sdk-core/" -L"/aws-sdk-cpp/aws-cpp-sdk-s3/build/aws-cpp-sdk-s3/" -L"/restbed/distribution/library" -L"/jsoncpp/build/debug/src/lib_json" -laws-cpp-sdk-core -laws-cpp-sdk-s3 -lrestbed -ljsoncpp


RUN cp /aws-sdk-cpp/aws-cpp-sdk-core/build/aws-cpp-sdk-core/libaws-cpp-sdk-core.so /usr/local/lib
RUN cp /aws-sdk-cpp/aws-cpp-sdk-s3/build/aws-cpp-sdk-s3/libaws-cpp-sdk-s3.so /usr/local/lib
RUN cp /restbed/distribution/library/librestbed.a /usr/local/lib
RUN cp /restbed/distribution/library/librestbed.so /usr/local/lib
RUN cp /restbed/distribution/library/librestbed.so.4 /usr/local/lib
RUN cp /restbed/distribution/library/librestbed.so.4.7 /usr/local/lib
RUN cp /jsoncpp/build/debug/src/lib_json/libjsoncpp.a /usr/local/lib


RUN cp /aws-sdk-cpp/aws-cpp-sdk-core/build/aws-cpp-sdk-core/libaws-cpp-sdk-core.so /lib
RUN cp /aws-sdk-cpp/aws-cpp-sdk-s3/build/aws-cpp-sdk-s3/libaws-cpp-sdk-s3.so /lib
RUN cp /restbed/distribution/library/librestbed.a /lib
RUN cp /restbed/distribution/library/librestbed.so /lib
RUN cp /restbed/distribution/library/librestbed.so.4 /lib
RUN cp /restbed/distribution/library/librestbed.so.4.7 /lib
RUN cp /jsoncpp/build/debug/src/lib_json/libjsoncpp.a /lib

RUN cp /aws-sdk-cpp/aws-cpp-sdk-core/build/aws-cpp-sdk-core/libaws-cpp-sdk-core.so /usr/lib
RUN cp /aws-sdk-cpp/aws-cpp-sdk-s3/build/aws-cpp-sdk-s3/libaws-cpp-sdk-s3.so /usr/lib
RUN cp /restbed/distribution/library/librestbed.a /usr/lib
RUN cp /restbed/distribution/library/librestbed.so /usr/lib
RUN cp /restbed/distribution/library/librestbed.so.4 /usr/lib
RUN cp /restbed/distribution/library/librestbed.so.4.7 /usr/lib
RUN cp /jsoncpp/build/debug/src/lib_json/libjsoncpp.a /usr/lib



# run the executable
CMD ["/home/ObjectsServer/ObjectsServer"]
