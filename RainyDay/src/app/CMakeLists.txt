project(RainyDay LANGUAGES CXX)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(project_sources src/main.cpp)
set(project_headers)

# wrap the ui file to a c++ header
qt5_wrap_cpp(moc_sources ${project_headers})

add_executable(RainyDay 
	${project_sources} 
	${project_headers}
	${ui_wrap} 
	${moc_sources})

target_link_libraries(RainyDay 
	LINK_PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets
	${freenect2_LIBRARIES}
	${OpenCV_LIBS}
	KinectControllers
	Memory)

	
# auto copy dlls if on windows
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)