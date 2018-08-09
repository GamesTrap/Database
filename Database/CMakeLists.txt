project(Database)

set( DATABASE_SOURCES
	src/main.cpp
	src/Database.h
	src/Database.cpp
	src/Record.h
	src/Record.cpp
	src/TextTable.h
	src/TextTable.cpp
	src/DatabaseInterface.h
	src/DatabaseInterface.cpp
)

add_executable(${PROJECT_NAME} ${DATABASE_SOURCES})