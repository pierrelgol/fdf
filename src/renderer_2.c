/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:44:47 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:44:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void renderer_init_world_data(t_renderer *const self, const int32_t width, const int32_t height)
{
	int32_t x;
	int32_t y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			self->world_coords[y][x] = vec3_mul(self->map_data->world_coords[y][x], vec3(WIDTH, HEIGHT, self->camera->amplitude));
			self->world_coords[y][x] = vec3_add(self->world_coords[y][x], self->camera->position);
			self->world_colors[y][x] = self->map_data->world_colors[y][x];
			++x;
		}
		++y;
	}
}

