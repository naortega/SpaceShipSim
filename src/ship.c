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

#include "ship.h"
#include "event_manager.h"
#include "globals.h"

#include <math.h>
#include <assert.h>
#include <allegro5/allegro_primitives.h>

#define SHIP_RADIUS 10.0f  // radius of the ship in pixels

void ship_init(struct ship *ship, float x, float y) {
	assert(ship);
	ship->x = x;
	ship->y = y;
	ship->velX = ship->velY = 0;
	ship->direction = 0;
}

void ship_update(struct ship *ship) {
	assert(ship);

	if(key_is_down(KEY_RIGHT))
		ship->direction += TURN_ACCEL;
	if(key_is_down(KEY_LEFT))
		ship->direction -= TURN_ACCEL;

	// keep direction within bounds
	if(ship->direction >= M_PI * 2)
		ship->direction -= M_PI * 2;
	else if(ship->direction < 0)
		ship->direction += M_PI * 2;

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

	ship->x += ship->velX;
	ship->y += ship->velY;
}

void ship_draw(struct ship *ship) {
	assert(ship);
	const float x0 = ship->x + (cos(ship->direction) *
			SHIP_RADIUS);
	const float y0 = ship->y + (sin(ship->direction) *
			SHIP_RADIUS);
	const float x1 = ship->x + (cos(ship->direction +
				M_PI * 0.8f) * SHIP_RADIUS);
	const float y1 = ship->y + (sin(ship->direction +
				M_PI * 0.8f) * SHIP_RADIUS);
	const float x2 = ship->x + (cos(ship->direction +
				M_PI * 1.2f) * SHIP_RADIUS);
	const float y2 = ship->y + (sin(ship->direction +
				M_PI * 1.2f) * SHIP_RADIUS);
	al_draw_filled_triangle(x0, y0, x1, y1, x2, y2,
			al_map_rgb(0xFF, 0x0, 0x0));
}
