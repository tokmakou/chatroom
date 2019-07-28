cmake_minimum_required(VERSION 3.8)
project(ChatRoom)

set(CMAKE_CXX_STANDARD 11)

# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


INCLUDE_DIRECTORIES(src)

file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE HDRS src/*.h)
file(GLOB_RECURSE UIFLS src/*.ui)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${UIFLS})

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
