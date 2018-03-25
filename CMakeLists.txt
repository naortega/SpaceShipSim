# Copyright (C) 2018  Ortega Froysa, Nicolás <nortega@themusicinnoise.net>
# Author: Ortega Froysa, Nicolás <nortega@themusicinnoise.net>
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

cmake_minimum_required(VERSION 2.8)
project(SpaceShipSim C)

set(TARGET_NAME "spaceshipsim")
set(TARGET_VERSION "0.3")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "release")
endif()

string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -O3")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os")

# TODO: detect libraries here
# TODO: set include directories here

set(SRCS
	src/main.c)

add_definitions(-DVERSION="${TARGET_VERSION}")

if(${CMAKE_BUILD_TYPE} STREQUAL "debug" OR
		${CMAKE_BUILD_TYPE} STREQUAL "relwithdebinfo")
	add_definitions(-DDEBUG)
else()
	add_definitions(-DNDEBUG)
endif()

add_executable(${TARGET_NAME} ${SRCS})

# TODO: link libraries

# TODO: create install instructions
