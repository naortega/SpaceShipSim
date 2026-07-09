/*
 * Copyright (C) 2026  Ortega Froysa, Nicolás <nicolas@ortegas.org>
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

#include "planet.h"
#include <cmath>
#include <cassert>
#include <allegro5/allegro_primitives.h>

#define GRAVITY_CONSTANT 1.0f    // Gravitational constant scaled for simulation
#define SHIP_MASS 1.0f           // Assumed constant ship mass
#define MASS_TO_RADIUS 1.5f      // Radius scale factor: radius = MASS_TO_RADIUS * mass^(1/3)

Planet::Planet(const float x, const float y, const float mass) :
	pos(x, y), mass(mass), radius(MASS_TO_RADIUS * cbrtf(mass))
{}

Vec<float> Planet::getGravity(const Ship &ship) const {
	const Vec<float> distance = this->pos - ship.getPos();

	if(distance.length() < this->radius)
		return Vec<float>(0, 0);

	// F = G * m1 * m2 / r^2
	const float force = GRAVITY_CONSTANT * SHIP_MASS * this->mass / (distance.length() * distance.length());

	// a = F / m_ship = G * m_this / r^2
	const float acceleration = force / SHIP_MASS;

	// Normalize direction and apply acceleration
	return distance.normalized() * acceleration;
}

void Planet::draw() {
	// Color intensity based on mass (brighter = more massive)
	float color_scale = fminf(1.0f, this->mass / 1000.0f);
	int r = (int)(100 + 155 * color_scale);
	int g = (int)(100 + 50 * color_scale);
	int b = (int)(150 - 100 * color_scale);

	al_draw_filled_circle(this->pos.x, this->pos.y, this->radius,
						  al_map_rgb(r, g, b));
}
