cmake_minimum_required(VERSION 3.10)
project(GeoJSONRouteComparator)

set(CMAKE_CXX_STANDARD 11)

add_executable(GeoJSONRouteComparator
    src/main.cpp
    src/GeoJSONRouteParser.cpp
    src/GeoJSONRouteComparator.cpp
    src/test.cpp
)

# add_library(test src/test.cpp)

# target_include_directories(test PRIVATE include)
# target_include_directories(test PRIVATE third_party/nholmann)


target_include_directories(GeoJSONRouteComparator PRIVATE include)
target_include_directories(GeoJSONRouteComparator PRIVATE third_party/nholmann)

