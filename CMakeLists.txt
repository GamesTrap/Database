cmake_minimum_required (VERSION 3.8)

project (Database)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_CXX_EXTENSIONS FALSE)

project(Database)

set( DATABASE_SOURCES
	src/main.cpp
)

add_executable(${PROJECT_NAME} ${DATABASE_SOURCES})