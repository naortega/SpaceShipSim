# Copyright (C) 2026  Ortega Froysa, Nicolás <nicolas@ortegas.org>
# Author: Ortega Froysa, Nicolás <nicolas@ortegas.org>
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

cmake_minimum_required(VERSION 3.10)
project(SpaceShipSim C)

set(TARGET_NAME "spaceshipsim")
set(TARGET_VERSION "0.5")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "release")
endif()

string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -ffast-math")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -O3 -ffast-math")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os")

find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEG5 REQUIRED allegro-5>=5.1.9)
pkg_check_modules(ALLEG5-PRIM REQUIRED allegro_primitives-5)
pkg_check_modules(ALLEG5-FONT REQUIRED allegro_font-5)

include_directories(
	SYSTEM ${ALLEG5_INCLUDE_DIRS})

set(SRCS
	src/event_manager.c
	src/main.c
	src/ship.c
	src/starfield.c)

add_definitions(-DVERSION="${TARGET_VERSION}")

if(${CMAKE_BUILD_TYPE} STREQUAL "debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "relwithdebinfo")
	add_definitions(-DDEBUG)
else()
	add_definitions(-DNDEBUG)
endif()

add_executable(${TARGET_NAME} ${SRCS})

target_link_libraries(${TARGET_NAME}
	m  # math library
	${ALLEG5_LIBRARIES}
	${ALLEG5-PRIM_LIBRARIES}
	${ALLEG5-FONT_LIBRARIES})

install(TARGETS ${TARGET_NAME}
	RUNTIME DESTINATION bin/
	CONFIGURATIONS release minsizerel)
