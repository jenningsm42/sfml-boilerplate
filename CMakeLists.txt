cmake_minimum_required(VERSION 3.1)

project(SFMLBoilerplate
        VERSION 1.0
        DESCRIPTION "SFML boilerplate code"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/main.cpp
        src/AnimatedSprite.cpp
        src/AssetCache.cpp
        src/Game.cpp
        src/GameScene.cpp
        src/InputHandler.cpp
        src/Player.cpp
        src/Scene.cpp
        src/SceneHandler.cpp
        src/GameObjectCollection.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
find_package(TGUI 0.8.3 REQUIRED)

add_executable(game ${SOURCE_FILES})

if (MSVC)
    target_compile_options(game PRIVATE /W4 /WX)
else (MSVC)
    target_compile_options(game PRIVATE -Wall -Wextra -pedantic -Werror)
endif (MSVC)

target_link_libraries(game tgui sfml-system sfml-window sfml-graphics sfml-audio)
