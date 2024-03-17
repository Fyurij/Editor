cmake_minimum_required(VERSION 3.15)

project(Editor)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(Editor
Editor.cpp
Commands.cpp
Message.cpp
main.cpp)

add_executable(EditorTest
EditorTest.cpp
Message.cpp)

target_link_libraries(
    EditorTest PRIVATE
    gtest gtest_main
)

target_compile_features(Editor PUBLIC cxx_std_17)
set_target_properties(Editor PROPERTIES CXX_STANDARD_REQUIRED ON)

target_compile_features(EditorTest PUBLIC cxx_std_17)
set_target_properties(EditorTest PROPERTIES CXX_STANDARD_REQUIRED ON)

add_custom_target(copyInputRecipe
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Recipe.txt ${CMAKE_BINARY_DIR}/Recipe.txt
)

add_custom_target(copyInputText
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Text.txt ${CMAKE_BINARY_DIR}/Text.txt
)

add_dependencies(Editor copyInputRecipe copyInputText)