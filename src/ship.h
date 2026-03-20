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

#include <allegro5/allegro.h>

struct ship {
	float x, y; ///< The x and y coordinates of the ship.
	float velX, velY; ///< The x and y velocities of the ship.
	/**
	 * The direction that the ship is facing in radians, where
	 * 0 is right facing.
	 */
	float direction;
};

/**
 * @brief Initialize the ship at a position.
 *
 * @param ship A pointer to the ship object.
 * @param x Initial x position of the ship.
 * @param y Initial y position of the ship.
 */
void ship_init(struct ship *ship, float x, float y);

/**
 * @brief Updates the ship's variables according to keyboard
 * input.
 *
 * @param ship A pointer to the ship object.
 */
void ship_update(struct ship *ship);

/**
 * @brief Draw the ship.
 *
 * @param ship Ship object to draw.
 */
void ship_draw(struct ship *ship);
