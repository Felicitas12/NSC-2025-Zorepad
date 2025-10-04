include(FetchContent)

#----------------------------------------------------------------------

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
message("Fetching glfw")
FetchContent_MakeAvailable(glfw)


#----------------------------------------------------------------------
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v2.0.8
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glad)
#----------------------------------------------------------------------

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG        master
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)

message("Fetching glm")
FetchContent_MakeAvailable(glm)
target_compile_definitions(glm INTERFACE GLM_FORCE_SILENT_WARNINGS)

#----------------------------------------------------------------------

FetchContent_Declare(
        stb_image
        GIT_REPOSITORY  https://github.com/nothings/stb.git
        GIT_TAG         master
        GIT_SHALLOW     TRUE
        GIT_PROGRESS    TRUE
)

FetchContent_GetProperties(stb_image)
if(NOT stb_image_POPULATED)
    FetchContent_Populate(stb_image)
    message("Fetching stb_image")

    # Убираем файл из add_library - для INTERFACE библиотеки не нужны источники
    add_library(stb_image INTERFACE)
    target_include_directories(stb_image INTERFACE ${stb_image_SOURCE_DIR})
endif()

# -------------------------------
# Bullet Physics
# -------------------------------
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        bullet
        GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
        GIT_TAG master
)
FetchContent_MakeAvailable(bullet)


# -------------------------------
# Assimp
# -------------------------------
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v6.0.2
)
message("Fetching assimp")
FetchContent_MakeAvailable(assimp)

# -------------------------------
# FreeType
# -------------------------------
FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
        GIT_TAG Master
)
FetchContent_MakeAvailable(freetype)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_MakeAvailable(yaml-cpp)

include(FetchContent)

# OpenAL Soft
FetchContent_Declare(
        openal-soft
        GIT_REPOSITORY https://github.com/kcat/openal-soft.git
        GIT_TAG master   # или конкретный релиз, например "1.23.1"
)

FetchContent_MakeAvailable(openal-soft)


FetchContent_Declare(
        libsndfile
        GIT_REPOSITORY https://github.com/libsndfile/libsndfile.git
        GIT_TAG        master
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(libsndfile)