project(Memory VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(project_sources memory_controller.cpp memory_model.cpp memory_view.cpp team_controller.cpp)
set(project_headers memory_controller.h memory_model.h memory_view.h game.h team_controller.h)


# wrap the ui file to a c++ header
add_library(Memory 
	${project_sources} 
	${project_headers})

target_link_libraries(Memory 
	PUBLIC
	KinectControllers
	GUI)


target_include_directories (Memory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})