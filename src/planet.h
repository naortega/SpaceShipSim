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

#include "ship.h"
#include "vec.h"

/**
 * Function pointer type for calculating planet mass.
 * Takes no parameters and returns the mass value.
 */
typedef float (*planet_mass_func)(void);

class Planet {
private:
	Vec<float> pos;      ///< The x and y coordinates of the planet center.
	const float mass;    ///< The mass of the planet.
	const float radius;  ///< The radius of the planet (derived from mass).

public:
	/**
	 * @brief Initialize a planet at a position with a specified mass.
	 *
	 * @param x Initial x position of the planet center.
	 * @param y Initial y position of the planet center.
	 * @param mass The mass of the planet.
	 */
	Planet(const float x, const float y, const float mass);

	/**
	 * @brief Calculate the gravitational acceleration on a ship at a given position.
	 *
	 * Returns the acceleration vector components due to the planet's gravity.
	 *
	 * @param ship Reference to ship.
	 *
	 * @returns A Vec<float> representing the gravitational acceleration (ax, ay).
	 */
	Vec<float> getGravity(const Ship &ship) const;

	/**
	 * @brief Draw the planet.
	 */
	void draw();
};
