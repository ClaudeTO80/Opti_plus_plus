cmake_minimum_required(VERSION 2.8)
project(AnalysisLib)
file(GLOB AnalysisLib_src
    "src/*.h"
    "src/*.cpp"
)
#message( ${AnalysisLib_src} )
add_library(AnalysisLib STATIC ${AnalysisLib_src})
include_directories(${AnalysisLib_src})
#add_test(toDoTest toDo)