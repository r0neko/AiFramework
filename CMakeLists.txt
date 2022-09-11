cmake_minimum_required(VERSION 3.13.0)

project(AiFramework VERSION 1.10.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_compile_definitions(_BUILD_AI_FRAMEWORK)
add_compile_definitions(_GL)

configure_file(templates/framework_config.hpp.in gen-include/framework_config.hpp)

file(GLOB_RECURSE AIFW_SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE AIFW_HEADER_FILES "include/*.hpp")

file(COPY assets shader DESTINATION "${CMAKE_BINARY_DIR}/output")

add_library(AiFramework SHARED "${AIFW_SOURCE_FILES}")
target_sources(AiFramework
        PUBLIC
        ${AIFW_HEADER_FILES}
        PRIVATE
        ${AIFW_SOURCE_FILES}
        )
target_include_directories(AiFramework PUBLIC include)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)

# requirements
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(AiFramework PUBLIC glm::glm)
target_link_libraries(AiFramework PUBLIC glad::glad)

if (WIN32)
    target_link_libraries(AiFramework PRIVATE opengl32)
endif (WIN32)