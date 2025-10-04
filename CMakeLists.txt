cmake_minimum_required(VERSION 3.29)
project(CallOfISS)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE EDITOR_SOURCES
        "src/*.cpp"
        "src/*.h"
)

add_executable(CallOfISS ${EDITOR_SOURCES})



add_library(Engine SHARED IMPORTED)

set_target_properties(Engine PROPERTIES
        IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/Engine.dll"       # путь до dll
        IMPORTED_IMPLIB   "${CMAKE_BINARY_DIR}/Engine.lib"       # путь до lib
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(CallOfISS PRIVATE Engine)


add_subdirectory(lib)

set(BULLET_SOURCES_DIR "${CMAKE_BINARY_DIR}/_deps/bullet-src")
set(SER_SOURCES_DIR "${CMAKE_BINARY_DIR}/_deps/serialize-src")
set(YOJ_SOURCES_DIR "${CMAKE_BINARY_DIR}/_deps/yojimbo-src")
set(GLAD_SOURCES_DIR "${CMAKE_BINARY_DIR}/_deps/glad-src")

add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)

glad_add_library(glad_gl_core_43 STATIC REPRODUCIBLE LOADER API gl:core=4.3)

target_link_libraries(CallOfISS PRIVATE
        glad_gl_core_43
        glfw
        glm
        BulletDynamics
        BulletCollision
        LinearMath
        assimp
        freetype
        yaml-cpp
        OpenAL
        sndfile
        stb_image
        )




target_include_directories(CallOfISS PUBLIC
        ${BULLET_SOURCES_DIR}/src
)
target_include_directories(CallOfISS INTERFACE
        ${SER_SOURCES_DIR}
)
target_include_directories(CallOfISS PUBLIC
        ${SER_SOURCES_DIR}
)

add_custom_command(TARGET CallOfISS POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
        COMMENT "Copying assets directory to build directory"
)