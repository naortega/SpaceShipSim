/*
 * Copyright (C) 2018,2026  Ortega Froysa, Nicolás <nicolas@ortegas.org>
 * Author: Ortega Froysa, Nicolás <nicolas@ortegas.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifndef VERSION
#	define VERSION "[version]"
#endif

#ifndef FPS
#	define FPS 60.0f
#endif
#ifndef ACCEL
#	define ACCEL 0.3f
#endif
#ifndef TURN_ACCEL
#	define TURN_ACCEL (M_PI / FPS)  // turn at pi radians / sec
#endif

#ifndef WINDOW_WIDTH
#	define WINDOW_WIDTH 800
#endif
#ifndef WINDOW_HEIGHT
#	define WINDOW_HEIGHT 600
#endif

#ifndef ZOOM_MIN
#	define ZOOM_MIN 0.25f
#endif
#ifndef ZOOM_MAX
#	define ZOOM_MAX 4.0f
#endif
#ifndef ZOOM_STEP
#	define ZOOM_STEP 0.1f
#endif

#include <math.h>
#ifndef M_PI
#	define M_PI 3.14159265f
#endif

#define RAD_TO_DEG(x) (x * 180 / M_PI)

#include <allegro5/allegro.h>

extern int redraw; ///< Whether or not to redraw the screen.
extern int run; ///< Whether or not to continue running the simulation.
extern int show_help; ///< Whether or not to show the help info.
extern int show_info; ///< Whether or not to show simulation info.
