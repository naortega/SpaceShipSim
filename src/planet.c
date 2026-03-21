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
#include <math.h>
#include <assert.h>
#include <allegro5/allegro_primitives.h>

#define GRAVITY_CONSTANT 1.0f  // Gravitational constant scaled for simulation
#define SHIP_MASS 1.0f           // Assumed constant ship mass
#define MASS_TO_RADIUS 1.5f      // Radius scale factor: radius = MASS_TO_RADIUS * mass^(1/3)

void planet_init(struct planet *planet, float x, float y, float mass) {
	assert(planet);

	planet->x = x;
	planet->y = y;
	planet->mass = mass;
	planet->radius = MASS_TO_RADIUS * cbrtf(planet->mass);
}

void planet_get_gravity(struct planet *planet, float ship_x, float ship_y,
						float *accel_x, float *accel_y) {
	assert(planet);
	assert(accel_x);
	assert(accel_y);

	float dx = planet->x - ship_x;
	float dy = planet->y - ship_y;
	float distance = sqrtf(dx * dx + dy * dy);

	if(distance < planet->radius) {
		*accel_x = 0.0f;
		*accel_y = 0.0f;
		return;
	}

	// F = G * m1 * m2 / r^2
	float force = GRAVITY_CONSTANT * SHIP_MASS * planet->mass / (distance * distance);

	// a = F / m_ship = G * m_planet / r^2
	float acceleration = force / SHIP_MASS;

	// Normalize direction and apply acceleration
	float norm_x = dx / distance;
	float norm_y = dy / distance;

	*accel_x = norm_x * acceleration;
	*accel_y = norm_y * acceleration;
}

void planet_draw(struct planet *planet) {
	assert(planet);

	// Color intensity based on mass (brighter = more massive)
	float color_scale = fminf(1.0f, planet->mass / 1000.0f);
	int r = (int)(100 + 155 * color_scale);
	int g = (int)(100 + 50 * color_scale);
	int b = (int)(150 - 100 * color_scale);

	al_draw_filled_circle(planet->x, planet->y, planet->radius,
			al_map_rgb(r, g, b));
}
