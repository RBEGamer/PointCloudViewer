cmake_minimum_required(VERSION 2.6)
project(point_cloud_viewer)

# Set version information in a config.h file
include_directories("${PROJECT_BINARY_DIR}")


file(GLOB helloworld_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
)


# Define sources and executable
set(EXECUTABLE_NAME "PointCloudViewer")
add_executable(${EXECUTABLE_NAME} ${helloworld_SRC})

find_package(OpenGL)
find_package(GLUT)
find_package(freenect2 REQUIRED)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})



# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)



# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARIES} ${SFML_LIBRARIES})
