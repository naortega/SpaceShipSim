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

#include "vec.h"
#include <allegro5/allegro.h>

class Ship {
private:
	/// Position of the ship in pixels.
	Vec<float> pos;
	/// Velocity of the ship in pixels per frame.
	Vec<float> vel;
	/**
	 * The direction that the ship is facing in radians, where
	 * 0 is right facing.
	 */
	float direction;

public:
	/**
	 * @brief Initialize ship.
	 *
	 * @param x Initial X position.
	 * @param y Initial Y position.
	 */
	Ship(const float x, const float y);

	/**
	 * @brief Updates the ship's variables according to keyboard
	 * input and gravitational forces.
	 *
	 * @param grav Vector of gravitational acceleration in pixels per frame squared.
	 */
	void update(const Vec<float> &grav);

	/**
	 * @brief Reset ship to position.
	 *
	 * @param x X position to reset to.
	 * @param y Y position to reset to.
	 */
	inline void reset(float x, float y) {
		this->pos.set(x, y);
		this->vel.set(0, 0);
		this->direction = 0;
	}

	/**
	 * @brief Draw the ship.
	 */
	void draw() const;

	inline Vec<float> getPos() const { return pos; }
	inline Vec<float> getVel() const { return vel; }
	inline float getDirection() const { return direction; }
};
