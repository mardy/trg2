#
# That Rabbit Game 2: Stone Age Rabbit Hunt
# Copyright (C) 2010, 2011, 2012, 2013 Thomas Perl <m@thp.io>
# http://thp.io/2011/trg2/
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 2.8)
project(ThatRabbitGame)

# Why, yes, we're rollin' C++11
set(CMAKE_CXX_FLAGS "-std=c++11")

# That Rabbit Game - Source code
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# External libraries: Image decoder and vincent font
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image.c")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

# Generated source: Texture atlas (C blob)
list(APPEND SOURCES "${CMAKE_CURRENT_BINARY_DIR}/l44_texture.c")


# Texture atlas to C source (requires xxd, which is usually shipped with vim)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/l44_texture.c
    COMMAND xxd -i ${CMAKE_CURRENT_SOURCE_DIR}/data/l44_texture.png |
            sed -e 's@'`echo ${CMAKE_CURRENT_SOURCE_DIR}/data |
            sed -e 's@/@_@g'`'_@@' >${CMAKE_CURRENT_BINARY_DIR}/l44_texture.c
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/data/l44_texture.png
)

file(GLOB SOUNDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/data/sounds" "${CMAKE_CURRENT_SOURCE_DIR}/data/sounds/*")
foreach(sound ${SOUNDS})
    string(REPLACE "." "_" resource ${sound})
    set(resource "resource-${resource}.c")
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${resource}
        COMMAND xxd -i ${CMAKE_CURRENT_SOURCE_DIR}/data/sounds/${sound} |
                sed -e 's@'`echo ${CMAKE_CURRENT_SOURCE_DIR}/data/sounds |
                sed -e 's@/@_@g'`'_@resource_@' >${CMAKE_CURRENT_BINARY_DIR}/${resource}
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/data/sounds/${sound}
    )
    list(APPEND SOURCES "${CMAKE_CURRENT_BINARY_DIR}/${resource}")
endforeach()

# We need SDL 1.2 for this to build
find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

# Platform-specific build of the main executable
IF(APPLE)
    find_library(FOUNDATION Foundation REQUIRED)
    find_library(OPENGL OpenGL REQUIRED)
    mark_as_advanced(FOUNDATION OPENGL)

    add_executable(trg2 MACOSX_BUNDLE ${SOURCES})
    target_link_libraries(trg2 ${SDL_LIBRARY} ${FOUNDATION} ${OPENGL})
ELSE()
    find_library(OPENGL GL REQUIRED)

    add_executable(trg2 ${SOURCES})
    target_link_libraries(trg2 ${SDL_LIBRARY} ${OPENGL})
ENDIF()

find_package(SDL_mixer)
IF(SDL_MIXER_FOUND)
    include_directories(${SDL_MIXER_INCLUDE_DIRS})
    target_link_libraries(trg2 ${SDL_MIXER_LIBRARIES})
    add_definitions(-DUSE_SDL_MIXER)
ENDIF()
