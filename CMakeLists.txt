cmake_minimum_required(VERSION 2.8)
project(AnalysisLib)

#OPTION(BUILD_TYPE "Build tests." OFF)

SET(BUILD_TYPE "Static" CACHE STRING "Static")

SET_PROPERTY(CACHE BUILD_TYPE PROPERTY STRINGS "Static" "Shared" "Both") 

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

file(GLOB AnalysisLib_src
    "src/*.h"
    "src/*.cpp"
)
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

include_directories(${AnalysisLib_src})
#add_test(toDoTest toDo)