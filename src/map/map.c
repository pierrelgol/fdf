/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:04:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 09:04:54 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool map_alloc(t_map *const self, const int32_t width, const int32_t height)
{
	int32_t index;

	if (!self || !width || !height)
		return (false);
	self->world_colors_buffer = memory_alloc(width * height * sizeof(int32_t));
	self->world_colors = memory_alloc(height * sizeof(int32_t *));
	if (!self->world_colors_buffer || !self->world_colors)
		return (false);
	self->world_coords_buffer = memory_alloc(width * height * sizeof(t_vec3));
	self->world_coords = memory_alloc(height * sizeof(t_vec3 *));
	if (!self->world_coords_buffer || !self->world_coords)
		return (false);
	index = 0;
	while (index < height)
	{
		self->world_colors[index] = &self->world_colors_buffer[index * width];
		self->world_coords[index] = &self->world_coords_buffer[index * width];
		++index;
	}
	return (true);
}

static void map_update_min_max(t_map *const self, const int32_t x, const int32_t y, const int32_t z)
{
	if (x < self->map_min.x)
		self->map_min.x = x;
	if (x > self->map_max.x)
		self->map_max.x = x;
	if (y < self->map_min.y)
		self->map_min.y = y;
	if (y > self->map_max.y)
		self->map_max.y = y;
	if (z < self->map_min.z)
		self->map_min.z = z;
	if (z > self->map_max.z)
		self->map_max.z = z;
}


static bool map_fill(t_map *const self, t_vector *const it, const int32_t width, const int32_t height)
{
	uintptr_t entry;
	int32_t   y;
	int32_t   x;

	if (!self || !it || !width || !height)
		return (false);
	y = 0;
	while (y < width && !it_end(it))
	{
		x = 0;
		while (x < width && !it_end(it))
		{
			entry = it_peek_curr(it);
			self->world_coords[y][x] = vec3(x, y, entry_get_zaxis(entry));
			self->world_colors[y][x] = entry_get_color(entry);
			map_update_min_max(self, x, y, entry_get_zaxis(entry));
			it_advance(it);
			++x;
		}
		++y;
	}
	return (true);
}

t_map *map_create(t_vector *const entries, const t_vec2 map_dim, const t_vec2 screen_dim)
{
	t_map *self;

	if (!entries || !map_dim.x || !map_dim.y || !screen_dim.x || !screen_dim.y)
		return (NULL);
	self = memory_alloc(sizeof(t_map));
	if (!self)
		return (NULL);
	if (!map_alloc(self, map_dim.x, map_dim.y))
		return (map_destroy(self));
	if (!map_fill(self, entries, map_dim.x, map_dim.y))
		return (map_destroy(self));
	self->map_width = map_dim.x;
	self->map_height = map_dim.y;
	self->map_center.x = (self->map_min.x + self->map_max.x) / 2.0f;
	self->map_center.y = (self->map_min.y + self->map_max.y) / 2.0f;
	self->map_center.z = (self->map_min.z + self->map_max.z) / 2.0f;
	self->screen_center.x = (0 +  WIDTH) / 2.0f;
	self->screen_center.y = (0 +  HEIGHT) / 2.0f;
	self->screen_center.z = (0.0f);
	self->screen_width = screen_dim.x;
	self->screen_height = screen_dim.y;
	return (self);
}

t_map *map_destroy(t_map *const self)
{
	if (self)
	{
		if (self->world_colors_buffer)
			memory_dealloc(self->world_colors_buffer);
		if (self->world_colors)
			memory_dealloc(self->world_colors);
		if (self->world_coords_buffer)
			memory_dealloc(self->world_coords_buffer);
		if (self->world_coords)
			memory_dealloc(self->world_coords);
		memory_dealloc(self);
	}
	return (NULL);
}
