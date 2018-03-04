cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project( OsgQt5 )

find_package(Qt5 REQUIRED COMPONENTS
        Widgets 
        Network
        OpenGL
        PrintSupport
        Gui
        )
find_package(OpenSceneGraph 3.4 REQUIRED osg osgDB osgAnimation osgUtil osgGA osgFX osgUtil osgViewer osgWidget osgText osgParticle)
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
if (UNIX)
find_package(X11)
endif(UNIX)

find_package(OpenGL REQUIRED)


# Instruct CMake to run moc automatically when needed.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )


# Add your source files here
set (SOURCES 
            main.cpp
            controlView.cpp
            mainWindow.cpp
            scene.cpp
            viewerWidget.cpp
)

# Add header files here
set (HEADERS
            controlView.h
            mainWindow.h
            scene.h
            viewerWidget.h
)
if (UNIX)
set(LinuxLibs ${X11_LIBRARIES})
endif (UNIX)
# set(OSG_NOTIFY_LEVEL DEBUG_FP)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} 
#             ${OPENGL_gl_LIBRARY}
#             /usr/lib64/librt.so
            Qt5::Widgets Qt5::Network Qt5::OpenGL Qt5::PrintSupport Qt5::Gui
			${OPENSCENEGRAPH_LIBRARIES}
			${LinuxLibs}
            )

