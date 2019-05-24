# At LEAST 2.8 but newer is better
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(RainyDayProject VERSION 0.1 LANGUAGES CXX)


# Set cmake prefix path to enable cmake to find freenect2
set(src/libs/libfreenect2/cmake_modules ${CMAKE_PREFIX_PATH} $ENV{HOME}/freenect2/lib/cmake/freenect2)
find_package(freenect2 REQUIRED)


INCLUDE_DIRECTORIES(
  ${freenect2_INCLUDE_DIR}
)

# Targets that we develop here
add_subdirectory(kinect_controller)
add_subdirectory(app)
