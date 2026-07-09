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

#include <cmath>
#include <cassert>
#include <allegro5/allegro_primitives.h>

#define SHIP_RADIUS 10.0f  // radius of the ship in pixels

Ship::Ship(const float x, const float y) :
	pos(x, y), vel(0, 0), direction(0)
{}

void Ship::update(const Vec<float> &grav) {
	if(key_is_down(KEY_RIGHT))
		this->direction += TURN_ACCEL;
	if(key_is_down(KEY_LEFT))
		this->direction -= TURN_ACCEL;

	// keep direction within bounds
	if(this->direction >= M_PI * 2)
		this->direction -= M_PI * 2;
	else if(this->direction < 0)
		this->direction += M_PI * 2;

	if(key_is_down(KEY_UP)) {
		this->vel.x += cos(this->direction) * ACCEL;
		this->vel.y += sin(this->direction) * ACCEL;
	}
	if(key_is_down(KEY_DOWN)) {
		// moving backwards is slower than moving forward
		this->vel.x -= cos(this->direction) * (ACCEL / 2);
		this->vel.y -= sin(this->direction) * (ACCEL / 2);
	}

	// Apply gravitational acceleration
	this->vel += grav;
	this->pos += this->vel;
}

void Ship::draw() const {
	const float x0 = this->pos.x + (cos(this->direction) * SHIP_RADIUS);
	const float y0 = this->pos.y + (sin(this->direction) * SHIP_RADIUS);
	const float x1 = this->pos.x + (cos(this->direction + M_PI * 0.8f) * SHIP_RADIUS);
	const float y1 = this->pos.y + (sin(this->direction + M_PI * 0.8f) * SHIP_RADIUS);
	const float x2 = this->pos.x + (cos(this->direction + M_PI * 1.2f) * SHIP_RADIUS);
	const float y2 = this->pos.y + (sin(this->direction + M_PI * 1.2f) * SHIP_RADIUS);
	al_draw_filled_triangle(x0, y0, x1, y1, x2, y2,
							al_map_rgb(0xFF, 0x0, 0x0));
}
