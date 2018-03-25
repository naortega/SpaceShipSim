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

#include "display.h"

#ifdef DEBUG
#	include <stdio.h>
#endif

int create_display(ALLEGRO_DISPLAY *display,
		unsigned int width, unsigned int height) {
	display = al_create_display(width, height);
	if(!display)
		return 0;
#ifdef DEBUG
	puts("Initialized display.");
#endif
	return 1;
}

void destroy_display(ALLEGRO_DISPLAY *display) {
	al_destroy_display(display);
#ifdef DEBUG
	puts("Destroyed display.");
#endif
}
