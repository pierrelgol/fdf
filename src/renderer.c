/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:04:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 11:04:54 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool renderer_alloc_screen_backend(t_renderer *const self, const int32_t width, const int32_t height)
{
	self->screen_height = height;
	self->screen_width = width;
	self->screen_coord_buffer = (t_vec2 *) memory_alloc(width * height * sizeof(t_vec2));
	if (!self->screen_coord_buffer)
		return (false);
	self->screen_color_buffer = (int32_t *) memory_alloc(width * height * sizeof(int32_t));
	if (!self->screen_color_buffer)
		return (false);
	return (true);
}

static bool renderer_alloc_world_backend(t_renderer *const self, const int32_t width, const int32_t height)
{
	self->world_height = height;
	self->world_width = width;
	self->world_coord_buffer = (t_vec3 *) memory_alloc(width * height * sizeof(t_vec3));
	if (!self->world_coord_buffer)
		return (false);
	self->world_color_buffer = (int32_t *) memory_alloc(width * height * sizeof(int32_t));
	if (!self->world_color_buffer)
		return (false);
	return (true);
}

t_renderer *renderer_create(const t_parser *const config, const int32_t screen_width, const int32_t screen_height)
{
	t_renderer *self;

	(void)screen_height;
	(void)screen_width;
	self = (t_renderer *) memory_alloc(sizeof(t_renderer));
	if (!self)
		return (NULL);
	self->parser = (t_parser*)config;
	if (!renderer_alloc_world_backend(self, config->parsed_width, config->parsed_height))
		return (renderer_destroy(self));
	if (!renderer_alloc_screen_backend(self, config->parsed_width, config->parsed_height))
		return (renderer_destroy(self));
	if (!renderer_init_world(self, config->parsed_width, config->parsed_height))
		return (renderer_destroy(self));
	if (!renderer_init_screen(self, config->parsed_width, config->parsed_height))
		return (renderer_destroy(self));
	self->z_amplitude = 1.0f;
	self->offset_zoom = 1.0f;
	return (self);
}

void renderer_init(t_renderer *const self)
{
	int32_t width;
	int32_t height;
	int32_t x;
	int32_t y;

	width = self->world_width;
	height = self->world_height;
	renderer_clear_world(self);
	renderer_clear_screen(self);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			self->world_coord[y][x] = vec3(x, y, self->parser->zaxis_matrix[y][x]);
			self->world_color[y][x] = color(self->parser->color_matrix[y][x]).color;
			++x;
		}
		++y;
	}
}

t_renderer *renderer_destroy(t_renderer *const self)
{
	if (self)
	{
		renderer_deinit_world(self);
		renderer_deinit_screen(self);
		memory_dealloc(self);
	}
	return (NULL);
}
