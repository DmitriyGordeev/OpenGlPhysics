cmake_minimum_required(VERSION 3.17)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(MyPhysics)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC
        "*.h"
        "*.cpp")

include_directories(C:/Users/User/Documents/ClionProjects/SDL2-2.0.12/include)
include_directories(C:/Users/User/Documents/ClionProjects/glm/glm)
include_directories(C:/Users/User/Documents/ClionProjects/glew-2.2.0-win32/glew-2.2.0/include)

# OpenGL:
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS})

# ----------------------------------------------------------------------
# SDL2 library:
link_directories(C:/Users/User/Documents/ClionProjects/SDL2-2.0.12/lib/x86/)

# GLEW library:
link_directories(C:/Users/User/Documents/ClionProjects/glew-2.2.0-win32/glew-2.2.0/lib/Release/Win32)


add_executable(MyPhysics ${SRC})

target_link_libraries(MyPhysics
        ${OPENGL_LIBRARIES}
        SDL2.lib
        SDL2main.lib
        glew32.lib
        glew32s.lib)





