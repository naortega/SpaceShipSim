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

#include "ship.h"
#include "event_manager.h"
#include "globals.h"

#ifdef DEBUG
#	include <stdio.h>
#endif
#include <math.h>

#ifndef M_PI
#	define M_PI 3.14159265f
#endif

#define ACCEL 5.0f
#define TURN_ACCEL (M_PI / FPS)  // turn at pi radians / sec

void ship_init(struct ship *ship, int x, int y) {
	if(!ship)
	{
#ifdef DEBUG
		fprintf(stderr,
				"ship_init(struct ship*,int,int): invalid ship.\n");
#endif
		return;
	}
	ship->x = x;
	ship->y = y;
	ship->velX = ship->velY = 0;
	ship->direction = 0;
}

void ship_update(struct ship *ship) {
	if(!ship)
	{
#ifdef DEBUG
		fprintf(stderr,
				"ship_update(struct ship*): invalid ship.\n");
#endif
		return;
	}

	if(key_is_down(KEY_UP))
	{
		ship->velX += cos(ship->direction) * ACCEL;
		ship->velY += sin(ship->direction) * ACCEL;
	}
	if(key_is_down(KEY_DOWN))
	{
		// moving backwards is slower than moving forward
		ship->velX -= cos(ship->direction) * (ACCEL / 2);
		ship->velY -= sin(ship->direction) * (ACCEL / 2);
	}
	if(key_is_down(KEY_RIGHT))
		ship->direction -= TURN_ACCEL;
	if(key_is_down(KEY_LEFT))
		ship->direction += TURN_ACCEL;

	// keep direction within bounds
	if(ship->direction >= M_PI * 2)
		ship->direction -= M_PI * 2;
	else if(ship->direction < 0)
		ship->direction += M_PI * 2;
}
