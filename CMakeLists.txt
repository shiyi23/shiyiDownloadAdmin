# CMakeList.txt : CMake project for shiyiDownloadAdmin, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("shiyiDownloadAdmin")

# Add source to this project's executable.
add_executable (shiyiDownloadAdmin "shiyiDownloadAdmin.cpp" "shiyiDownloadAdmin.h")

# TODO: Add tests and install targets if needed.
    find_package(CURL CONFIG REQUIRED)
    target_link_libraries(shiyiDownloadAdmin public CURL::libcurl)