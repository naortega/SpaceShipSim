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

#pragma once

/**
 * Function pointer type for calculating planet mass.
 * Takes no parameters and returns the mass value.
 */
typedef float (*planet_mass_func)(void);

struct planet {
	float x, y;       ///< The x and y coordinates of the planet center.
	float mass;       ///< The mass of the planet.
	float radius;     ///< The radius of the planet (derived from mass).
};

/**
 * @brief Initialize a planet at a position with a specified mass.
 *
 * @param planet A pointer to the planet object.
 * @param x Initial x position of the planet center.
 * @param y Initial y position of the planet center.
 * @param mass The mass of the planet.
 */
void planet_init(struct planet *planet, float x, float y, float mass);

/**
 * @brief Calculate the gravitational acceleration on a ship at a given position.
 *
 * Returns the acceleration vector components due to the planet's gravity.
 *
 * @param planet A pointer to the planet object.
 * @param ship_x X position of the ship.
 * @param ship_y Y position of the ship.
 * @param accel_x Pointer to store the x component of acceleration.
 * @param accel_y Pointer to store the y component of acceleration.
 */
void planet_get_gravity(struct planet *planet, float ship_x, float ship_y,
						float *accel_x, float *accel_y);

/**
 * @brief Draw the planet.
 *
 * @param planet Planet object to draw.
 */
void planet_draw(struct planet *planet);
