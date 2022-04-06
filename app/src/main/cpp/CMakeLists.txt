#[[
 CMake file to build C++ HTTP server on Android
]]

cmake_minimum_required(VERSION 3.18)
project(tanca_server LANGUAGES C CXX)


#=========================================================================================================================
# BOOST
#=========================================================================================================================
include(FetchContent)

FetchContent_Declare(
        boost_project
        URL      https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.bz2
)

FetchContent_GetProperties(boost_project)
if(NOT boost_project_POPULATED)
    FetchContent_Populate(boost_project)
endif()

FetchContent_MakeAvailable(boost_project)
# add_subdirectory(${boost_project_SOURCE_DIR} BOOST)

add_library(tanca_server SHARED
        main_backend.cpp
        http_server.cpp
        efs.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${boost_project_SOURCE_DIR})

# Include libraries needed for TarotClub lib
target_link_libraries(tanca_server
                      android
                      log)

# End of Cmake file
