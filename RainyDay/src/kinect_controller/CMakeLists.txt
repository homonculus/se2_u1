project(KinectControllers VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("/usr/include/libusb-1.0/")

find_package( OpenCV REQUIRED )
include_directories( %{OpenCV_INCLUDE_DIRS} ) 

set(project_sources kinect_controller.cpp grid_controller.cpp kinect_tests.cpp)
set(project_headers kinect_controller.h grid_controller.h)


# wrap the ui file to a c++ header
add_library(KinectControllers 
	${project_sources} 
	${project_headers})

target_link_libraries(KinectControllers 
	PUBLIC
	${freenect2_LIBRARIES}
	${OpenCV_LIBS})


target_include_directories (KinectControllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})