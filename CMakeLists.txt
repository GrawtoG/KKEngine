cmake_minimum_required(VERSION 4.2)
project(KKEngine)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)



FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/GrawtoG/raylib.git
        GIT_TAG        master
        GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(raylib)


add_executable(KKEngine main.cpp
        src/core/Engine.cpp
        src/core/Engine.hxx
        src/core/Scene.cpp
        src/core/Scene.hxx
        src/core/GameObject.cpp
        src/core/GameObject.hxx
        src/core/Component.cpp
        src/core/Component.hxx
        src/KK/Time.cpp
        src/KK/Time.hxx
        src/components/Transform.cpp
        src/components/Transform.hxx
        src/components/Renderer.cpp
        src/components/Renderer.hxx

)
target_link_libraries(KKEngine PRIVATE raylib)