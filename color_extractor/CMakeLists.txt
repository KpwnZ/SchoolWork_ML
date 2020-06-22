cmake_minimum_required(VERSION 2.8)

project(color_extractor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    include
)

add_executable(color_extractor 
    utils.cpp
    main.cpp
)
target_link_libraries(color_extractor  
    ${OpenCV_LIBS}
)
