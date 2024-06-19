/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:42:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:42:43 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_renderer *renderer_alloc(t_renderer *const self, int32_t y,  const int32_t width, const int32_t height)
{
	self->world_colors_buffer = memory_alloc(width * height * sizeof(int32_t));
	self->world_coords_buffer = memory_alloc(width * height * sizeof(t_vec3));
	self->world_colors = memory_alloc(height * sizeof(int32_t *));
	self->world_coords = memory_alloc(height * sizeof(t_vec3 *));
	self->screen_colors_buffer = memory_alloc(width * height * sizeof(int32_t));
	self->screen_coords_buffer = memory_alloc(width * height * sizeof(t_vec2));
	self->screen_colors = memory_alloc(height * sizeof(int32_t *));
	self->screen_coords = memory_alloc(height * sizeof(t_vec2 *));
	if (!self->world_colors || !self->world_coords || !self->world_colors_buffer || !self->world_coords_buffer)
		return (NULL);
	if (!self->screen_colors || !self->screen_coords || !self->screen_colors_buffer || !self->screen_coords_buffer)
		return (NULL);
	y = 0;
	while (y < height)
	{
		self->world_coords[y] = &self->world_coords_buffer[y * width];
		self->world_colors[y] = &self->world_colors_buffer[y * width];
		self->screen_coords[y] = &self->screen_coords_buffer[y * width];
		self->screen_colors[y] = &self->screen_colors_buffer[y * width];
		++y;
	}
	return (self);
}

t_renderer *renderer_create(t_fdf_container *const fdf, t_camera *const camera, t_map *const map)
{
	t_renderer *self;

	self = memory_alloc(sizeof(t_renderer));
	if (!self)
		return (NULL);
	self->mlx_handle = fdf->mlx_handle;
	self->win_handle = fdf->win_handle;
	self->img_handle = fdf->img_handle;
	self->img_buffer = fdf->img_buffer;
	self->img_endian = fdf->img_endian;
	self->map_data = map;
	self->img_size = fdf->img_size;
	self->img_bpp = fdf->img_bpp;
	self->camera = camera;
	self->height = map->height;
	self->width = map->width;
	if (!renderer_alloc(self, 0, map->width, map->height))
		return (renderer_destroy(self));
	return (self);
}

t_renderer	*renderer_destroy(t_renderer *const self)
{
	if (self)
	{
		if (self->world_colors_buffer)
			memory_dealloc(self->world_colors_buffer);
		if (self->world_coords_buffer)
			memory_dealloc(self->world_coords_buffer);
		if (self->world_colors)
			memory_dealloc(self->world_colors);
		if (self->world_coords)
			memory_dealloc(self->world_coords);
		if (self->screen_colors_buffer)
			memory_dealloc(self->screen_colors_buffer);
		if (self->screen_coords_buffer)
			memory_dealloc(self->screen_coords_buffer);
		if (self->screen_colors)
			memory_dealloc(self->screen_colors);
		if (self->screen_coords)
			memory_dealloc(self->screen_coords);
		memory_dealloc(self);
	}
	return (NULL);
}
