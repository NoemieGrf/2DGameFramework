cmake_minimum_required(VERSION 3.2)

project(2DGameFrameWork)

set(TARGET_NAME game)
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/artifacts/)

file(GLOB_RECURSE SRC_FIELS src/*.cpp)

add_executable(${TARGET_NAME} ${SRC_FIELS})

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nlohmann/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sfml/include/
)

target_link_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sfml/lib/
)

target_compile_definitions(${TARGET_NAME} PRIVATE SFML_STATIC)

set(SFML_DEBUG_LIB sfml-graphics-s-d.lib sfml-window-s-d.lib sfml-system-s-d.lib)
set(SFML_RELEASE_LIB sfml-graphics-s.lib sfml-window-s.lib sfml-system-s.lib)
set(SFML_COMMON_LIB opengl32.lib freetype.lib winmm.lib gdi32.lib)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_link_libraries(${TARGET_NAME} PRIVATE ${SFML_COMMON_LIB} ${SFML_DEBUG_LIB})
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    target_link_libraries(${TARGET_NAME} PRIVATE ${SFML_COMMON_LIB} ${SFML_RELEASE_LIB})
endif()

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND cd ./scripts
    COMMAND echo [PostBuild] copy assets...
    COMMAND python assets_copy.py
    COMMAND echo [PostBuild] copy config...
    COMMAND python config_copy.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)