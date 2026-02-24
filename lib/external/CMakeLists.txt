include(FetchContent)

FetchContent_Declare(
    lib-glad
    GIT_REPOSITORY http://gitlab.kicon.fri.uniza.sk/mrena/lib-glad.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glad
)

FetchContent_Declare(
    lib-glfw
    GIT_REPOSITORY http://gitlab.kicon.fri.uniza.sk/mrena/lib-glfw.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw
)

FetchContent_Declare(
    lib-imgui
    GIT_REPOSITORY http://gitlab.kicon.fri.uniza.sk/mrena/lib-imgui.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

FetchContent_Declare(
    lib-stb
    GIT_REPOSITORY http://gitlab.kicon.fri.uniza.sk/mrena/lib-stb.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stb
)

FetchContent_Declare(
lib-nlohmann
GIT_REPOSITORY https://github.com/nlohmann/json.git
GIT_TAG v3.12.0
SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann
)

FetchContent_MakeAvailable(lib-glad)

FetchContent_MakeAvailable(lib-glfw)

FetchContent_MakeAvailable(lib-imgui)

FetchContent_MakeAvailable(lib-stb)

