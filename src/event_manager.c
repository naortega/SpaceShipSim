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
#include <allegro5/allegro.h>

static ALLEGRO_EVENT_QUEUE *event_queue;
static ALLEGRO_TIMER *timer;

int evnt_mngr_init() {
	timer = al_create_timer(1.0f / FPS);
	if(!timer)
		return 0;
#ifdef DEBUG
	puts("Initialized timer.");
#endif

	event_queue = al_create_event_queue();
	if(!event_queue)
		return 0;
#ifdef DEBUG
	puts("Initialized event queue.");
#endif
	al_register_event_source(event_queue,
			al_get_display_event_source(display));
	al_register_event_source(event_queue,
			al_get_timer_event_source(timer));
	al_start_timer(timer);
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

void handle_event() {
	ALLEGRO_EVENT evnt;
	al_wait_for_event(event_queue, &evnt);

	if(evnt.type == ALLEGRO_EVENT_TIMER)
		redraw = 1;
	else if(evnt.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		run = 0;
}
