project(KinectControllers VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Set cmake prefix path to enable cmake to find freenect2
set(src/libs/libfreenect2/cmake_modules ${CMAKE_PREFIX_PATH} $ENV{HOME}/freenect2/lib/cmake/freenect2)
find_package(freenect2 REQUIRED)

include_directories("/usr/include/libusb-1.0/")

find_package( OpenCV REQUIRED )
include_directories( %{OpenCV_INCLUDE_DIRS} ) 

INCLUDE_DIRECTORIES(
  ${freenect2_INCLUDE_DIR}
)

set(project_sources kinect_controller.cpp main.cpp)
set(project_headers kinect_controller.h)


# wrap the ui file to a c++ header
add_library(KinectControllers 
	${project_sources} 
	${project_headers})

target_link_libraries(KinectControllers 
	PUBLIC
	${freenect2_LIBRARIES}
	${OpenCV_LIBS})


target_include_directories (KinectControllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})