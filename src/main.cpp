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

#include "globals.h"
#include "event_manager.h"
#include "ship.h"
#include "starfield.h"
#include "planet.h"
#include "vec.h"

int run;
int redraw;
int show_help;
int show_info;

#include <cstdlib>
#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

const char *help =
	"HELP:\n"
	"LEFT/RIGHT - turn the ship\n"
	"UP/DOWN - accelerate/reverse accelerate\n"
	"R - reset the simulation\n"
	"P - pause/unpause the simulation\n"
	"I - show/hide simulation information\n"
	"H - show/hide this help information\n"
	"F - toggle fullscreen\n"
	"Z - zoom in\n"
	"SHIFT+Z - zoom out\n"
	"Q/ESC - quit";

const char *info_format =
	"INFO:\n"
	"x: %f\n"
	"y: %f\n"
	"angle: %f (%f degrees)\n"
	"velX: %f px/sec\n"
	"velY: %f px/sec";

struct allegro_components {
	int primitives_addon;
	int font_addon;
	ALLEGRO_DISPLAY *display;
	int evnt_system;
	ALLEGRO_FONT *font;
};

void cleanup_allegro(struct allegro_components *allegro) {
	if(allegro->font) {
		al_destroy_font(allegro->font);
#ifdef DEBUG
		std::cout << "[DEBUG] Destroyed font." << std::endl;
#endif
		allegro->font = nullptr;
	}
	if(allegro->evnt_system) {
		evnt_mngr_deinit();
		allegro->evnt_system = 0;
	}
	if(allegro->display) {
		al_destroy_display(allegro->display);
#ifdef DEBUG
		std::cout << "[DEBUG] Destroyed display." << std::endl;
#endif
		allegro->display = nullptr;
	}
	if(allegro->font_addon) {
		al_shutdown_font_addon();
#ifdef DEBUG
		std::cout << "[DEBUG] Shutdown font addon." << std::endl;
#endif
		allegro->font_addon = 0;
	}
	if(allegro->primitives_addon) {
		al_shutdown_primitives_addon();
#ifdef DEBUG
		std::cout << "[DEBUG] Shutdown primitives addon." << std::endl;
#endif
		allegro->primitives_addon = 0;
	}
}

int main() {
	const std::string title = "SpaceShipSim v" + std::string(VERSION);
	float zoom = 1.0f;
	float display_width = WINDOW_WIDTH;
	float display_height = WINDOW_HEIGHT;
	struct allegro_components allegro __attribute__((cleanup(cleanup_allegro))) = {
		0,
		0,
		nullptr,
		0,
		nullptr
	};

	std::cout << title << std::endl;

	if(!al_init()) {
		fprintf(stderr, "alleg5: failed to initialize Allegro.\n");
		return EXIT_FAILURE;
	}
#ifdef DEBUG
	std::cout << "[DEBUG] Initialized allegro system." << std::endl;
#endif
	if(!(allegro.primitives_addon = al_init_primitives_addon())) {
		fprintf(stderr, "alleg5: failed to initialize primitives addon.\n");
		return EXIT_FAILURE;
	}
#ifdef DEBUG
	std::cout << "[DEBUG] Initialized primitives addon." << std::endl;
#endif

	if(!(allegro.font_addon = al_init_font_addon())) {
		fprintf(stderr, "alleg5: failed to initialize font addon.\n");
		return EXIT_FAILURE;
	}
#ifdef DEBUG
	std::cout << "[DEBUG] Initialized font addon." << std::endl;
#endif

	allegro.display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	if(!allegro.display) {
		fprintf(stderr, "alleg5: failed to initialize display.\n");
		return EXIT_FAILURE;
	}
	al_set_window_title(allegro.display, title.c_str());
#ifdef DEBUG
	std::cout << "[DEBUG] Created display." << std::endl;
#endif

	if(!(allegro.evnt_system = evnt_mngr_init(allegro.display))) {
		fprintf(stderr, "alleg5: failed to initialize event queue.\n");
		return EXIT_FAILURE;
	}

	// initialize the spaceship at the center of the screen
	Ship ship(400, 300);

	// initialize the planet
	Planet planet(400.0f, 300.0f, 250.0f);

	allegro.font = al_create_builtin_font();
#ifdef DEBUG
	std::cout << "[DEBUG] Created font." << std::endl;
#endif

	// begin running the simulation
	run = 1;
	redraw = 1;
	show_help = 1;
	show_info = 1;
	int paused = 0;
	int old_paused = 0;
	int just_toggled_fullscreen = 0;
	int zoom_pressed = 0;

	while(run) {
		handle_event();

		// only redraw or run simulation if the timer event has occurred
		if(redraw) {
			if(just_toggled_fullscreen) {
				display_width = al_get_display_width(allegro.display);
				display_height = al_get_display_height(allegro.display);
			}

			if(paused == old_paused && key_is_down(KEY_PAUSE))
				paused = !paused;
			else if(paused != old_paused && !key_is_down(KEY_PAUSE))
				old_paused = paused;

			if(!paused) {
				if(key_is_down(KEY_RESET))
					ship.reset((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
				else {
					ship.update(planet.getGravity(ship));
				}
			}

			if (key_is_down(KEY_FULLSCREEN) && !just_toggled_fullscreen) {
				if(al_get_display_flags(allegro.display) & ALLEGRO_FULLSCREEN_WINDOW)
					al_set_display_flag(allegro.display, ALLEGRO_FULLSCREEN_WINDOW, 0);
				else
					al_set_display_flag(allegro.display, ALLEGRO_FULLSCREEN_WINDOW, 1);

				just_toggled_fullscreen = 1;
			} else if (!key_is_down(KEY_FULLSCREEN) && just_toggled_fullscreen) {
				just_toggled_fullscreen = 0;
			}

			if(key_is_down(KEY_SHIFT) && key_is_down(KEY_ZOOM) && !zoom_pressed) {
				zoom -= ZOOM_STEP;
				if(zoom < ZOOM_MIN)
					zoom = ZOOM_MIN;
				zoom_pressed = 1;
			} else if(key_is_down(KEY_ZOOM) && !zoom_pressed) {
				zoom += ZOOM_STEP;
				if(zoom > ZOOM_MAX)
					zoom = ZOOM_MAX;
				zoom_pressed = 1;
			} else if(!key_is_down(KEY_ZOOM) && zoom_pressed) {
				zoom_pressed = 0;
			}

			al_clear_to_color(al_map_rgb(0, 0, 0));

			ALLEGRO_TRANSFORM transform;
			al_identity_transform(&transform);
			al_scale_transform(&transform, zoom, zoom);
			al_translate_transform(&transform,
								   display_width / 2.0f - ship.getPos().x * zoom,
								   display_height / 2.0f - ship.getPos().y * zoom);
			al_use_transform(&transform);

			starfield_draw(ship.getPos().x, ship.getPos().y, zoom,
						   display_width, display_height);
			planet.draw();
			ship.draw();

			al_identity_transform(&transform);
			al_use_transform(&transform);

			if(show_info) {
				char info[256];
				sprintf(info, info_format,
						ship.getPos().x, ship.getPos().y,
						ship.getDirection(),
						RAD_TO_DEG(ship.getDirection()),
						ship.getVel().x * FPS, ship.getVel().y * FPS);
				al_draw_multiline_text(allegro.font,
						al_map_rgb(0xFF, 0xFF, 0xFF),
						5, 5, (int)display_width, 10.0f,
						ALLEGRO_ALIGN_LEFT,
						info);
			}

			if(show_help) {
				al_draw_multiline_text(allegro.font,
						al_map_rgb(0xFF, 0xFF, 0xFF),
						display_width / 2, display_height / 2 - 50,
						(int)display_width, 10.0f,
						ALLEGRO_ALIGN_CENTRE,
						help);
			}
			al_flip_display();
			redraw = 0;
		}
	}

	return EXIT_SUCCESS;
}
