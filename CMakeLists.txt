cmake_minimum_required(VERSION 3.10)
project(ur VERSION 0.1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# find libopenmpt, using pkg-config:
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(OPENMPT REQUIRED IMPORTED_TARGET libopenmpt)

find_package(libopenmpt CONFIG REQUIRED)

# Define the executable
add_executable(ur src/ur.cpp src/audio/audio.cpp src/game/map.cpp src/game/object.cpp src/ui/menu.cpp src/ui/titlescreen.cpp src/graphics/font.cpp src/graphics/layer.cpp src/graphics/sprite.cpp)

if(SDL2_FOUND)
    message(STATUS "SDL2_INCLUDE_DIRS = ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL2_LIBRARIES = ${SDL2_LIBRARIES}")
    # include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(ur SDL2::SDL2)
else()
    message(FATAL_ERROR "SDL2 not found")
endif()

if(SDL2_image_FOUND )
    # message(STATUS "SDL2_image_INCLUDE_DIRS = ${SDL2_image_INCLUDE_DIRS}")
    # message(STATUS "SDL2_image_LIBRARIES = ${SDL2_image_LIBRARIES}")
    target_link_libraries(ur SDL2_image::SDL2_image)
else()
    message(FATAL_ERROR "SDL2_image not found")
endif()

if(libopenmpt_FOUND)
    message(STATUS "OPENMPT_INCLUDE_DIRS = ${OPENMPT_INCLUDE_DIRS}")
    message(STATUS "OPENMPT_LIBRARIES = ${OPENMPT_LIBRARIES}")
    # include_directories(${OPENMPT_INCLUDE_DIRS})
    # target_link_libraries(ur ${OPENMPT_LIBRARIES})
    target_link_libraries(ur libopenmpt::libopenmpt)
else()
    message(FATAL_ERROR "libopenmpt not found")
endif()

# Include directories
include_directories(src src/audio src/graphics src/ui)

# Add subdirectory
add_subdirectory(src)

# Link libraries
target_link_libraries(ur)

# Compiler flags
target_compile_options(ur PRIVATE -Wall)

# Game data
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
