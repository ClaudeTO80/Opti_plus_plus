cmake_minimum_required(VERSION 3.13.2)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(AnalysisLib VERSION 0.1.0.0)

include(CTest)

set(PROJECT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
message( "Compiling version ${PROJECT_VERSION_STRING}" )
message( "Generating file src/version.h" )

file(WRITE src/version.h
"#define PRJ_VERSION ${PROJECT_VERSION_STRING}\n\
#define PRJ_VERSION_MAJOR ${PROJECT_VERSION_MAJOR}\n\
#define PRJ_VERSION_MINOR ${PROJECT_VERSION_MINOR}\n\
#define PRJ_VERSION_PATCH ${PROJECT_VERSION_PATCH}\n\
#define PRJ_VERSION_TWEAK ${PROJECT_VERSION_TWEAK}\n" )
#add_test(toDoTest toDo)

#OPTION(BUILD_TYPE "Build tests." OFF)

SET(BUILD_TYPE "Static" CACHE STRING "Static")

SET_PROPERTY(CACHE BUILD_TYPE PROPERTY STRINGS "Static" "Shared" "Both") 

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

file(GLOB AnalysisLib_src "src/*.h" "src/*.cpp")
#message( ${AnalysisLib_src} )
IF(${BUILD_TYPE} MATCHES "Static" OR ${BUILD_TYPE} MATCHES "Both")
	add_library(AnalysisLib STATIC ${AnalysisLib_src})
	
	set_target_properties( AnalysisLib 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	OUTPUT_NAME "AnalysisLib"
#	COMPILE_FLAGS "-m32" 
#	LINK_FLAGS "-m32"
)

ENDIF()

IF(${BUILD_TYPE} MATCHES "Shared" OR ${BUILD_TYPE} MATCHES "Both")
	add_library(AnalysisLibShared SHARED ${AnalysisLib_src})


set_target_properties( AnalysisLibShared
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	OUTPUT_NAME "AnalysisLib"
#	COMPILE_FLAGS "-m32" 
#	LINK_FLAGS "-m32"
)
ENDIF()

include_directories("src")
if(BUILD_TESTING)
	file(GLOB testFullFact_src "test/src/*.cpp")
	
	add_executable(testFullFact  ${testFullFact_src})
	include_directories("../../src")
	target_link_libraries(testFullFact AnalysisLib) 
endif()

#configure_file(version.h.in version.h)
