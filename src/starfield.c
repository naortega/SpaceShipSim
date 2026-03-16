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

#include "starfield.h"
#include "globals.h"

#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define CHUNK_SIZE 256
#define STARS_PER_CHUNK 50
#define STAR_COLOR al_map_rgb(255, 255, 255)

static unsigned int hash_seed(int chunk_x, int chunk_y) {
	unsigned int h = 5381;
	h = ((h << 5) + h) ^ chunk_x;
	h = ((h << 5) + h) ^ chunk_y;
	return h;
}

static void generate_chunk_stars(int chunk_x, int chunk_y) {
	unsigned int seed = hash_seed(chunk_x, chunk_y);
	srand(seed);

	float base_x = chunk_x * CHUNK_SIZE;
	float base_y = chunk_y * CHUNK_SIZE;

	for(int i = 0; i < STARS_PER_CHUNK; ++i)
	{
		float star_x = base_x + (float)(rand() % CHUNK_SIZE);
		float star_y = base_y + (float)(rand() % CHUNK_SIZE);

		al_draw_pixel(star_x, star_y, STAR_COLOR);
	}
}

void starfield_draw(float camera_x, float camera_y, float zoom, float width, float height) {
	float view_width = width / zoom;
	float view_height = height / zoom;

	float left = camera_x - view_width / 2.0f;
	float right = camera_x + view_width / 2.0f;
	float top = camera_y - view_height / 2.0f;
	float bottom = camera_y + view_height / 2.0f;

	int chunk_left = (int)floor(left / CHUNK_SIZE);
	int chunk_right = (int)floor(right / CHUNK_SIZE);
	int chunk_top = (int)floor(top / CHUNK_SIZE);
	int chunk_bottom = (int)floor(bottom / CHUNK_SIZE);

	for(int cy = chunk_top; cy <= chunk_bottom; ++cy)
	{
		for(int cx = chunk_left; cx <= chunk_right; ++cx)
		{
			generate_chunk_stars(cx, cy);
		}
	}
}
