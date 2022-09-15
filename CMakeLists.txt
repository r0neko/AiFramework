cmake_minimum_required(VERSION 3.13.0)
project(AiFramework VERSION 1.13.23)

# define standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# configure CMake dirs in order to detect vendor dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/config")

# generate files
configure_file("templates/framework_config.hpp.in" "${CMAKE_BINARY_DIR}/generated/include/framework_config.hpp")

# include code
file(GLOB_RECURSE AIFW_SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE AIFW_HEADER_FILES "include/*.hpp" "${CMAKE_BINARY_DIR}/generated/include")

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_BINARY_DIR}/generated/include")

# define the library
add_library(AiFramework SHARED ${AIFW_SOURCE_FILES})

# define sources
target_sources(AiFramework
        PUBLIC
        ${AIFW_HEADER_FILES}
        PRIVATE
        ${AIFW_SOURCE_FILES}
        )

# mandatory dependencies
find_package(glm CONFIG REQUIRED)

# add include dirs to be accessible by everyone
target_include_directories(AiFramework PUBLIC include)
target_include_directories(AiFramework PUBLIC "${GLM_INCLUDE_DIRS}")

# configuration
option(AIFW_USE_OPENGL "Adds OpenGL support to AiFramework. It uses GLAD internally to load OpenGL." ON)

set(AIFW_LIBS glm::glm)
set(AIFW_COMPILE_FLAGS _BUILD_AI_FRAMEWORK _AI_FRAMEWORK_CONFIG)

if (AIFW_USE_OPENGL)
    find_package(glad CONFIG REQUIRED)

    list(APPEND AIFW_COMPILE_FLAGS _GL)
    list(APPEND AIFW_LIBS glad::glad)
endif ()

# platform specific stuff
if (WIN32)
    list(APPEND AIFW_COMPILE_FLAGS _WINDOWS)
    list(APPEND AIFW_LIBS opengl32)
endif ()

if (LINUX)
    list(APPEND AIFW_COMPILE_FLAGS _LINUX)
endif ()

if (ANDROID)
    list(APPEND AIFW_COMPILE_FLAGS _ANDROID)
    list(APPEND AIFW_LIBS android log EGL GLESv3)
endif ()

add_compile_definitions(${AIFW_COMPILE_FLAGS})
target_link_libraries(AiFramework ${AIFW_LIBS})