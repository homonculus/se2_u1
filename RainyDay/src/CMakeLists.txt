# At LEAST 2.8 but newer is better
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(RainyDayProject VERSION 0.1 LANGUAGES CXX)

# Targets that we develop here
add_subdirectory(kinect_controllers)
add_subdirectory(app)
