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
 * @brief Draw stars in the visible area of the starfield.
 *
 * @param camera_x The x position of the camera center.
 * @param camera_y The y position of the camera center.
 * @param zoom The zoom level (scale factor).
 * @param width The display width in pixels.
 * @param height The display height in pixels.
 */
void starfield_draw(float camera_x, float camera_y, float zoom, float width, float height);
