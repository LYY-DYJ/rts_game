cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/rts_game)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

add_subdirectory(src)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)
set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(json)


install(DIRECTORY game/img DESTINATION ${PROJECT_BINARY_DIR}/rts_game)
install(DIRECTORY game/content DESTINATION ${PROJECT_BINARY_DIR}/rts_game)
install(DIRECTORY game/font DESTINATION ${PROJECT_BINARY_DIR}/rts_game)
