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

enum {
	KEY_UP          = 0x0,
	KEY_DOWN        = 0x1,
	KEY_LEFT        = 0x2,
	KEY_RIGHT       = 0x3,
	KEY_RESET       = 0x4,
	KEY_FULLSCREEN  = 0x5,
	KEY_MAX         = 0x6
};

/**
 * @brief Initialize the event handler.
 *
 * @param display A pointer to the display (used to get
 * event source).
 *
 * @return 0 upon failure, 1 upon success.
 */
int evnt_mngr_init(ALLEGRO_DISPLAY *display);

/**
 * @brief Deinitialize the event handler.
 */
void evnt_mngr_deinit();

/**
 * @brief Handle the next event in the queue (wait if the
 * queue is empty).
 */
void handle_event();

/**
 * @brief Receive state of a key.
 *
 * @param code The key code.
 *
 * @return If down 1 will be returned, else 0.
 */
int key_is_down(int code);
