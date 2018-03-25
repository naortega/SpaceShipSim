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
#include "event_manager.h"
#include "ship.h"

int run;
int redraw;
int show_help;
int show_info;

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

const char *help =
	"HELP:\n"
	"LEFT/RIGHT - turn the ship\n"
	"UP/DOWN - accelerate/decelerate\n"
	"I - show/hide simulation information\n"
	"H - show/hide this help information\n"
	"Q/ESC - quit";

const char *info_format =
	"INFO:\n"
	"x: %f\n"
	"y: %f\n"
	"angle: %f (%f degrees)\n"
	"velX: %f\n"
	"velY: %f";

int main() {
	printf("SpaceShipSim v%s\n", VERSION);

	if(!al_init())
	{
		fprintf(stderr, "alleg5: failed to initialize Allegro.\n");
		return 1;
	}
#ifdef DEBUG
	puts("Initialized allegro system.");
#endif
	if(!al_init_primitives_addon())
	{
		fprintf(stderr, "alleg5: failed to initialize primitives addon.\n");
		return 1;
	}
#ifdef DEBUG
	puts("Initialized primitives addon.");
#endif

	if(!al_init_font_addon())
	{
		fprintf(stderr, "alleg5: failed to initialize font addon.\n");
		return 1;
	}

	ALLEGRO_DISPLAY *display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	if(!display)
	{
		fprintf(stderr, "alleg5: failed to initialize display.\n");
		return 1;
	}
#ifdef DEBUG
	puts("Created display.");
#endif

	if(!evnt_mngr_init(display))
	{
		fprintf(stderr, "alleg5: failed to initialize event queue.\n");
		al_destroy_display(display);
		return 1;
	}

	// initialize the spaceship at the center of the screen
	struct ship ship;
	ship_init(&ship, 400, 300);

	ALLEGRO_FONT *font = al_create_builtin_font();

	// begin running the simulation
	run = 1;
	redraw = 1;
	show_help = 1;
	show_info = 1;
	while(run)
	{
		handle_event();

		// only redraw or run simulation if the timer event has occurred
		if(redraw)
		{
			/*
			 * We only run the simulation when the timer goes off so it's
			 * running at a consistent rate, rather than dependent on random
			 * events.
			 */
			ship_update(&ship);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			ship_draw(&ship);
			if(show_info)
			{
				char info[256];
				sprintf(info, info_format,
						ship.x, ship.y,
						ship.direction,
						RAD_TO_DEG(ship.direction),
						ship.velX, ship.velY);
				al_draw_multiline_text(font,
						al_map_rgb(0xFF, 0xFF, 0xFF),
						5, 5, WINDOW_WIDTH, 10.0f,
						ALLEGRO_ALIGN_LEFT,
						info);
			}

			if(show_help)
			{
				al_draw_multiline_text(font,
						al_map_rgb(0xFF, 0xFF, 0xFF),
						WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
						WINDOW_WIDTH, 10.0f,
						ALLEGRO_ALIGN_CENTRE,
						help);
			}
			al_flip_display();
			redraw = 0;
		}
	}

	al_destroy_font(font);
	evnt_mngr_deinit();
	al_destroy_display(display);
#ifdef DEBUG
	puts("Destroyed display.");
#endif
	al_shutdown_font_addon();
#ifdef DEBUG
	puts("Shutdown font addon.");
#endif
	al_shutdown_primitives_addon();
#ifdef DEBUG
	puts("Shutdown primitives addon.");
#endif

	return 0;
}
