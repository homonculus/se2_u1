project(GUI LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(project_sources grid.cpp memory_game_window.cpp kinect_worker.cpp memory_param_window.cpp kinect_event_window.cpp memory_callibration_label.cpp)
set(project_headers grid.h memory_game_window.h kinect_worker.h memory_param_window.h kinect_event.h kinect_event_window.h memory_callibration_label.h)

# wrap the ui file to a c++ header
qt5_wrap_cpp(moc_sources ${project_headers})

add_library(GUI 
	${project_sources} 
	${project_headers}
	${moc_sources})


target_link_libraries(GUI 
	LINK_PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets
	KinectControllers)

target_include_directories (GUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
	
# auto copy dlls if on windows
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)