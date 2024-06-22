/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:58:37 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 11:58:37 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	renderer_world_fill(t_renderer *const self, const int32_t width,
		const int32_t height)
{
	int32_t	y;
	int32_t	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			self->rendered[y][x] = vec3(self->world[y][x].x,
					self->world[y][x].y, self->colors[y][x]);
			self->rendered[y][x].x += self->screen_center.x;
			self->rendered[y][x].y += self->screen_center.y;
			++x;
		}
		++y;
	}
}
