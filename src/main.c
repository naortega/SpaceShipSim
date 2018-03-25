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

#include "globals.h"
#include "display.h"
#include "event_manager.h"

int run;
int redraw;

#include <stdio.h>
#include<allegro5/allegro.h>

int main() {
	printf("SpaceShipSim v%s\n", VERSION);

	if(!al_init())
	{
		fprintf(stderr, "alleg5: failed to initialize Allegro.\n");
		return 1;
	}
	if(!create_display(800, 600))
	{
		fprintf(stderr, "alleg5: failed to create display.\n");
		return 1;
	}

	if(!evnt_mngr_init())
	{
		fprintf(stderr, "alleg5: failed to initialize event queue.\n");
		destroy_display();
		return 1;
	}

	// begin running the simulation
	run = 1;
	redraw = 1;
	while(run)
	{
		handle_event();
		// TODO: run simulation physics

		// only redraw if the timer event has occurred
		if(redraw)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			// TODO: run simulation draw functions
			al_flip_display();
			redraw = 0;
		}
	}

	evnt_mngr_deinit();
	destroy_display();

	return 0;
}
