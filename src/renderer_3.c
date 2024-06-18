/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:17:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 10:17:42 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	renderer_init_screen(t_renderer *const self, const int32_t width,
		const int32_t height)
{
	int32_t	index;

	if (!self || !width || !height)
		return (false);
	self->screen_coord = (t_vec2 **)memory_alloc(height * sizeof(t_vec2 *));
	self->screen_color = (int32_t **)memory_alloc(height * sizeof(int32_t *));
	if (!self->screen_color || !self->screen_coord)
		return (false);
	index = 0;
	while (index < height)
	{
		self->screen_coord[index] = &self->screen_coord_buffer[index * width];
		self->screen_color[index] = &self->screen_color_buffer[index * width];
		++index;
	}
	return (true);
}

bool	renderer_clear_screen(t_renderer *const self)
{
	if (!self)
		return (false);
	if (!self->screen_color_buffer || !self->screen_coord_buffer)
		return (false);
	memory_fill(self->screen_coord_buffer, 0x00, self->screen_height
		* self->screen_width * sizeof(t_vec2));
	memory_fill(self->screen_color_buffer, 0x00, self->screen_height
		* self->screen_width * sizeof(int32_t));
	return (true);
}

bool	renderer_deinit_screen(t_renderer *const self)
{
	if (self)
	{
		if (self->screen_coord_buffer)
			memory_dealloc(self->screen_coord_buffer);
		if (self->screen_color_buffer)
			memory_dealloc(self->screen_color_buffer);
		if (self->screen_color)
			memory_dealloc(self->screen_color);
		if (self->screen_coord)
			memory_dealloc(self->screen_coord);
		return (true);
	}
	return (false);
}
