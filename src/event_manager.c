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

#include "event_manager.h"
#include "globals.h"

#ifdef DEBUG
#	include <stdio.h>
#endif
#include <stddef.h>
#include <allegro5/allegro.h>

static ALLEGRO_EVENT_QUEUE *event_queue;
static ALLEGRO_TIMER *timer;
static int keys[KEY_MAX];

int evnt_mngr_init() {
	if(!al_install_keyboard())
		return 0;
#ifdef DEBUG
	puts("Initialized keyboard.");
#endif

	timer = al_create_timer(1.0f / FPS);
	if(!timer)
		return 0;
#ifdef DEBUG
	puts("Initialized timer.");
#endif

	event_queue = al_create_event_queue();
	if(!event_queue)
	{
		al_destroy_timer(timer);
		return 0;
	}
#ifdef DEBUG
	puts("Initialized event queue.");
#endif
	al_register_event_source(event_queue,
			al_get_display_event_source(display));
	al_register_event_source(event_queue,
			al_get_timer_event_source(timer));
	al_start_timer(timer);

	// set all keys to false at initialization
	for(size_t i = 0; i < KEY_MAX; ++i)
		keys[i] = 0;

	return 1;
}

void evnt_mngr_deinit() {
	al_destroy_timer(timer);
#ifdef DEBUG
	puts("Destroyed timer.");
#endif
	al_destroy_event_queue(event_queue);
#ifdef DEBUG
	puts("Destroyed event queue.");
#endif
}

void set_key(int keycode, int value) {
	int key_index = -1;
	switch(keycode)
	{
		case ALLEGRO_KEY_UP:
			key_index = KEY_UP;
			break;
		case ALLEGRO_KEY_DOWN:
			key_index = KEY_DOWN;
			break;
		case ALLEGRO_KEY_LEFT:
			key_index = KEY_LEFT;
			break;
		case ALLEGRO_KEY_RIGHT:
			key_index = KEY_RIGHT;
			break;
		case ALLEGRO_KEY_R:
			key_index = KEY_RESET;
			break;
		case ALLEGRO_KEY_H:
			key_index = KEY_HELP;
			break;
		case ALLEGRO_KEY_I:
			key_index = KEY_INFO;
			break;
		case ALLEGRO_KEY_F:
			key_index = KEY_FULLSCREEN;
			break;
		default:
			key_index = -1;
			break;
	}
	if(key_index != -1)
		keys[key_index] = value;
}

void handle_event() {
	ALLEGRO_EVENT evnt;
	al_wait_for_event(event_queue, &evnt);

	switch(evnt.type)
	{
		case ALLEGRO_EVENT_TIMER:
			redraw = 1;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			run = 0;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			set_key(evnt.keyboard.keycode, 1);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			set_key(evnt.keyboard.keycode, 0);
			break;
	}
}

int key_is_down(int code) {
	if(code < 0 || code >= KEY_MAX)
	{
#ifdef DEBUG
		fprintf(stderr, "key_is_down(int): bad key code!\n");
#endif
		return 0;
	}
	else
		return keys[code];
}
