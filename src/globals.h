/*
 * Copyright (C) 2018  Ortega Froysa, Nicolás <nortega@themusicinnoise.net>
 * Author: Ortega Froysa, Nicolás <nortega@themusicinnoise.net>
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
#	define ACCEL 0.5f
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

#include <allegro5/allegro.h>

extern int redraw; ///< Whether or not to redraw the screen.
extern int run; ///< Whether or not to continue running the simulation.
extern int show_help; ///< Whether or not to show the help info.
extern int show_info; ///< Whether or not to show simulation info.
