cmake_minimum_required(VERSION 3.10.0)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(Opti++ VERSION 0.1.0.0)

include(CTest)

set(PROJECT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
message( "Compiling version ${PROJECT_VERSION_STRING}" )
message( "Generating file include/version.h" )

file(WRITE include/version.h
"#define PRJ_VERSION ${PROJECT_VERSION_STRING}\n\
#define PRJ_VERSION_MAJOR ${PROJECT_VERSION_MAJOR}\n\
#define PRJ_VERSION_MINOR ${PROJECT_VERSION_MINOR}\n\
#define PRJ_VERSION_PATCH ${PROJECT_VERSION_PATCH}\n\
#define PRJ_VERSION_TWEAK ${PROJECT_VERSION_TWEAK}\n" )
#add_test(toDoTest toDo)

#OPTION(BUILD_TYPE "Build tests." OFF)

#SET(BUILD_TYPE "Static" CACHE STRING "Static")

#SET_PROPERTY(CACHE BUILD_TYPE PROPERTY STRINGS "Static" "Shared" "Both") 

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
	#SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRe") 
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif(MSVC)

file(GLOB AnalysisLib_src "src/*.cpp")
#message( ${AnalysisLib_src} )
#IF(${BUILD_TYPE} MATCHES "Static" OR ${BUILD_TYPE} MATCHES "Both")
	add_library(OptiLib STATIC ${AnalysisLib_src})
	
	set_target_properties( OptiLib 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	OUTPUT_NAME "OptiLib"
#	COMPILE_FLAGS "-m32" 
#	LINK_FLAGS "-m32"
)

#ENDIF()

#IF(${BUILD_TYPE} MATCHES "Shared" OR ${BUILD_TYPE} MATCHES "Both")
#	add_library(AnalysisLibShared SHARED ${AnalysisLib_src})


#set_target_properties( AnalysisLibShared
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#	OUTPUT_NAME "AnalysisLib"
##	COMPILE_FLAGS "-m32" 
##	LINK_FLAGS "-m32"
#)
##ENDIF()

include_directories("include")
if(BUILD_TESTING)
	file(GLOB testFullFact_src "test/test_FullFactorial.cpp")
	add_executable(testFullFact  ${testFullFact_src})
	include_directories("../../include")
	target_link_libraries(testFullFact OptiLib) 
	
	file(GLOB testFullFact_RD_src "test/test_FullFactorial_RD.cpp")
	add_executable(testFullFact_RD  ${testFullFact_RD_src})
	include_directories("../../include")
	target_link_libraries(testFullFact_RD OptiLib) 
	
	file(GLOB testLatinHyper_src "test/test_LatinHypercube.cpp")
	add_executable(testLatinHyper  ${testLatinHyper_src})
	include_directories("../../include")
	target_link_libraries(testLatinHyper OptiLib) 
	
endif()

#configure_file(version.h.in version.h)
