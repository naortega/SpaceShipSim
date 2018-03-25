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

#pragma once

#include <allegro5/allegro.h>

/**
 * @brief Create an allegro 5 display with a given width and height.
 *
 * @param display The display to create.
 * @param width The width of the display.
 * @param height The height of the display.
 *
 * @return If successful it will return 1, else it will return 0.
 */
int create_display(ALLEGRO_DISPLAY *display,
		unsigned int width, unsigned int height);

/**
 * @brief Destroy the display (used for shutdown).
 *
 * @param display The display to destroy.
 */
void destroy_display(ALLEGRO_DISPLAY *display);
