cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)

# name the project
project(2DGameFrameWork)

# build the exe
set(TARGET_NAME game)

file(GLOB_RECURSE SRC_FILES src/*.cpp) # my file
file(GLOB_RECURSE BOX2D_FILES ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/box2d/src/*.cpp) # box2d source files
file(GLOB_RECURSE SPINE_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spine-cpp/src/*.cpp) # box2d source files
file(GLOB_RECURSE SPINE_SFML_FILES ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spine-sfml/src/*.cpp) # box2d source files

add_executable(${TARGET_NAME}
        ${SRC_FILES}
        ${BOX2D_FILES}
        ${SPINE_CPP_FILES}
        ${SPINE_SFML_FILES}
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/artifacts/) # CMAKE_CURRENT_SOURCE_DIR: the directory of current CMakeLists.txt

# PREPROCESS & LINK
# -------------------------------------------------------------------------------------------------
# additional macro
target_compile_definitions(${TARGET_NAME} PRIVATE SFML_STATIC) 

# additional include directories
target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nlohmann/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sfml/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/box2d/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spine-cpp/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spine-sfml/include/
)

# additional static lib directories
target_link_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sfml/lib/
) 

# set specific lib
set(SFML_COMMON_LIB opengl32.lib freetype.lib winmm.lib gdi32.lib) # required in both debug & relase
set(SFML_DEBUG_LIB sfml-graphics-s-d.lib sfml-window-s-d.lib sfml-system-s-d.lib) # required in debug
set(SFML_RELEASE_LIB sfml-graphics-s.lib sfml-window-s.lib sfml-system-s.lib) # required in release

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_link_libraries(${TARGET_NAME} PRIVATE ${SFML_COMMON_LIB} ${SFML_DEBUG_LIB})
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    target_link_libraries(${TARGET_NAME} PRIVATE ${SFML_COMMON_LIB} ${SFML_RELEASE_LIB})
endif()
# -------------------------------------------------------------------------------------------------

# post build event
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND cd ./scripts
    COMMAND echo [PostBuild] copy assets/ to artifacts/assets/
    COMMAND python assets_copy.py
    COMMAND echo [PostBuild] copy config/ to artifacts/config/
    COMMAND python config_copy.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)