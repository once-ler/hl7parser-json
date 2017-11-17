cmake_minimum_required(VERSION 3.2)

project(testing VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-fno-stack-protector")

set(XML2JSON ${PROJECT_SOURCE_DIR}/../../xml2json/include)

include_directories(
    /usr/local/include
    "${PROJECT_SOURCE_DIR}/include"
    "${XML2JSON}"
)

set(CPP_SOURCES
    "${PROJECT_SOURCE_DIR}/test.cpp"
)

add_executable(testing ${CPP_SOURCES})

target_link_libraries(
    testing
    libhl7parser.so
)
