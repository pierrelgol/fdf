/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:17:33 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 10:17:33 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	renderer_init_world(t_renderer *const self, const int32_t width,
		const int32_t height)
{
	int32_t	index;

	if (!self || !width || !height)
		return (false);
	self->world_coord = (t_vec3 **)memory_alloc(height * sizeof(t_vec3 *));
	self->world_color = (int32_t **)memory_alloc(height * sizeof(int32_t *));
	if (!self->world_color || !self->world_coord)
		return (false);
	index = 0;
	while (index < height)
	{
		self->world_coord[index] = &self->world_coord_buffer[index * width];
		self->world_color[index] = &self->world_color_buffer[index * width];
		++index;
	}
	return (true);
}

bool	renderer_clear_world(t_renderer *const self)
{
	if (!self)
		return (false);
	if (!self->world_color_buffer || !self->world_coord_buffer)
		return (false);
	memory_fill(self->world_coord_buffer, 0x00, self->world_height
		* self->world_width * sizeof(t_vec3));
	memory_fill(self->world_color_buffer, 0x00, self->world_height
		* self->world_width * sizeof(int32_t));
	return (true);
}

bool	renderer_deinit_world(t_renderer *const self)
{
	if (self)
	{
		if (self->world_coord_buffer)
			memory_dealloc(self->world_coord_buffer);
		if (self->world_color_buffer)
			memory_dealloc(self->world_color_buffer);
		if (self->world_color)
			memory_dealloc(self->world_color);
		if (self->world_coord)
			memory_dealloc(self->world_coord);
		return (true);
	}
	return (false);
}
