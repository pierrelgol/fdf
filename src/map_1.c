/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:58:48 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 11:58:50 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void	map_print(t_map *const self)
{
	printf("MAP DATA\n");
	for (int i = 0; i < self->height; ++i)
	{
		for (int j = 0; j < self->width; ++j)
		{
			printf("{%.6f,%.6f,%.6f}",self->world_coords[i][j].x,self->world_coords[i][j].y, self->world_coords[i][j].z);
		}
		printf("\n");
	}
}

static void	map_normalize_world_coords(t_map *const self, const int32_t width,
		const int32_t height)
{
	// t_vec3	delta;
	t_vec3	coord;
	int32_t	y;
	int32_t	x;

	y = 0;
	// delta = vec3_delta(self->world_min, self->world_max);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			coord = self->world_coords[y][x];
			self->world_coords[y][x] = coord;
			++x;
		}
		++y;
	}
}

t_map	*map_alloc(t_map *const self, t_parser *const config,
		const int32_t width, const int32_t height)
{
	int32_t	y;

	self->world_colors_buffer = memory_alloc(width * height * sizeof(int32_t));
	if (!self->world_colors_buffer)
		return (NULL);
	self->world_coords_buffer = memory_alloc(width * height * sizeof(t_vec3));
	if (!self->world_coords_buffer)
		return (NULL);
	self->world_colors = memory_alloc(height * sizeof(int32_t *));
	if (!self->world_colors)
		return (NULL);
	self->world_coords = memory_alloc(height * sizeof(t_vec3 *));
	if (!self->world_coords)
		return (NULL);
	memory_copy(self->world_colors_buffer, config->map_colors_buffer, width
		* height * sizeof(int32_t));
	memory_copy(self->world_coords_buffer, config->map_coords_buffer, width
		* height * sizeof(t_vec3));
	y = 0;
	while (y < height)
	{
		self->world_colors[y] = &self->world_colors_buffer[y * width];
		self->world_coords[y] = &self->world_coords_buffer[y * width];
		++y;
	}
	return (self);
}

t_map	*map_create(t_parser *const config, const int32_t width,
		const int32_t height)
{
	t_map	*self;

	self = (t_map *)memory_alloc(sizeof(t_map));
	if (!self)
		return (NULL);
	self->height = height;
	self->width = width;
	self->inputs = config;
	self->world_min = config->map_min;
	self->world_max = config->map_max;
	if (!map_alloc(self, config, width, height))
		return (map_destroy(self));
	map_normalize_world_coords(self, width, height);
	// map_print(self);
	return (self);
}

t_map	*map_clone(t_map *const self)
{
	return (map_create(self->inputs, self->width, self->height));
}

t_map	*map_destroy(t_map *const self)
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
		memory_dealloc(self);
	}
	return (NULL);
}

