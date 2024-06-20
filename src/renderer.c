/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:44:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/20 10:44:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_renderer *renderer_alloc(t_renderer *const self, const int32_t width, const int32_t height)
{
	self->height = height;
	self->width = width;
	self->screen_color_buffer = memory_alloc(width * height * sizeof(int32_t));
	self->screen_color = memory_alloc(height * sizeof(int32_t *));
	self->screen_coord_buffer = memory_alloc(width * height * sizeof(t_vec2));
	self->screen_coord = memory_alloc(height * sizeof(t_vec2 *));

	self->world_color_buffer = memory_alloc(width * height * sizeof(int32_t));
	self->world_color = memory_alloc(height * sizeof(int32_t *));
	self->world_coord_buffer = memory_alloc(width * height * sizeof(t_vec3));
	self->world_coord = memory_alloc(height * sizeof(t_vec3 *));

	self->ratio_h = ((float_t) HEIGHT / height);
	self->ratio_w = ((float_t) WIDTH / width);
	for (int32_t i = 0; i < height; ++i)
	{
		self->world_color[i] = &self->world_color_buffer[i * width];
		self->world_coord[i] = &self->world_coord_buffer[i * width];
		self->screen_color[i] = &self->screen_color_buffer[i * width];
		self->screen_coord[i] = &self->screen_coord_buffer[i * width];
	}
	return (self);
}

t_renderer *renderer_create(t_fdf_container *const fdf, const t_parser *const config, const int32_t width, const int32_t height)
{
	t_renderer *self;

	self = (t_renderer *) memory_alloc(sizeof(t_renderer));
	if (!self)
		return (NULL);
	self->mlx_handle = fdf->mlx_handle;
	self->win_handle = fdf->win_handle;
	self->img_handle = fdf->img_handle;
	self->img_buffer = fdf->img_buffer;
	self->img_endian = fdf->img_endian;
	self->img_size = fdf->img_size;
	self->img_bpp = fdf->img_bpp;
	self->parser = (t_parser *) config;
	self->camera = fdf->camera;
	if (!renderer_alloc(self, width, height))
		return (NULL);
	return (self);
}

void renderer_init(t_renderer *const self, const int32_t width, const int32_t height)
{
	t_vec3  v;
	int32_t x;
	int32_t y;
	int32_t c;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			v = vec3(x, y, self->parser->zaxis_matrix[y][x]);
			c = color(self->parser->color_matrix[y][x]).color;
			self->world_coord[y][x] = v;
			self->world_color[y][x] = c;
			++x;
		}
		++y;
	}
	world_print(self->world_coord, width, height);
}

t_renderer *renderer_destroy(t_renderer *const self)
{
	if (self)
	{
		if (self->world_color_buffer)
			memory_dealloc(self->world_color_buffer);
		if (self->world_coord_buffer)
			memory_dealloc(self->world_coord_buffer);
		if (self->world_color)
			memory_dealloc(self->world_color);
		if (self->world_coord)
			memory_dealloc(self->world_coord);
		if (self->screen_color_buffer)
			memory_dealloc(self->screen_color_buffer);
		if (self->screen_coord_buffer)
			memory_dealloc(self->screen_coord_buffer);
		if (self->screen_color)
			memory_dealloc(self->screen_color);
		if (self->screen_coord)
			memory_dealloc(self->screen_coord);
		memory_dealloc(self);
	}
	return (NULL);
}
