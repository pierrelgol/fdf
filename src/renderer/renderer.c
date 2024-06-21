/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:04:32 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 10:04:32 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <string.h>

static bool renderer_alloc(t_renderer *const self, const int32_t width, const int32_t height)
{
	int32_t y;

	self->world = memory_alloc((height) * sizeof(t_vec3 *));
	self->colors = memory_alloc((height)* sizeof(int32_t *));
	if (!self->world || !self->colors)
		return (false);
	self->rendered_buffer = memory_alloc(width * (height )* sizeof(t_vec3));
	self->rendered = memory_alloc((height) * sizeof(t_vec3 *));
	if (!self->rendered_buffer || !self->rendered)
		return (false);
	y = 0;
	while (y < height)
	{
		self->rendered[y] = &self->rendered_buffer[y * width];
		++y;
	}
	return (true);
}

t_renderer *renderer_create(t_map *const map, t_camera *const camera, const int32_t width, const int32_t height)
{
	t_renderer *self;

	if (!map || !camera || !height || !width)
		return (NULL);
	self = memory_alloc(sizeof(t_renderer));
	if (!self)
		return (NULL);
	if (!renderer_alloc(self, width, height))
		return (renderer_destroy(self));
	self->map = map;
	self->camera = camera;
	self->projection = camera->projection;
	self->screen_height = HEIGHT;
	self->screen_width = WIDTH;
	self->world_height = height;
	self->world_width = width;
	self->world_center = map->map_center;
	self->screen_center = map->screen_center;
	return (self);
}

bool renderer_init(t_renderer *const self, t_map *const map, const int32_t width, const int32_t height)
{
	int32_t y;

	if (!self || !map || !width || !height)
		return (false);
	self->projection = self->camera->projection;
	self->world_buffer = map_clone_world_coords_buffer(map);
	self->colors_buffer = map_clone_world_colors_buffer(map);
	if (!self->world_buffer || !self->colors_buffer)
		return (false);
	y = 0;
	while (y < height)
	{
		self->world[y] = &self->world_buffer[y * width];
		self->colors[y] = &self->colors_buffer[y * width];
		++y;
	}
	return (true);
}

bool renderer_deinit(t_renderer *const self, const int32_t width, const int32_t height)
{
	if (!self || !width || !height)
		return (false);
	if (self->world_buffer)
		memory_dealloc(self->world_buffer);
	if (self->colors_buffer)
		memory_dealloc(self->colors_buffer);
	self->world_buffer = NULL;
	self->colors_buffer = NULL;
	memset(self->world, 0x00, height * sizeof(t_vec3 *));
	memset(self->colors, 0x00, height * sizeof(int32_t *));
	memset(self->rendered_buffer, 0x00, (width * height * sizeof(t_vec3)));
	return (true);
}

t_renderer *renderer_destroy(t_renderer *const self)
{
	if (self)
	{
		if (self->world_buffer)
			memory_dealloc(self->world_buffer);
		if (self->world)
			memory_dealloc(self->world);
		if (self->colors_buffer)
			memory_dealloc(self->colors_buffer);
		if (self->colors)
			memory_dealloc(self->colors);
		if (self->rendered_buffer)
			memory_dealloc(self->rendered_buffer);
		if (self->rendered)
			memory_dealloc(self->rendered);
		memory_dealloc(self);
	}
	return (NULL);
}
