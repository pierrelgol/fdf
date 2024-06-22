/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_project.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:55:26 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 11:55:26 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	renderer_project_isometric(t_vec3 *const vec)
{
	double	temp_x;
	double	temp_y;

	temp_x = vec->x;
	temp_y = vec->y;
	vec->x = (temp_x - temp_y) * COS30;
	vec->y = -vec->z + (temp_x + temp_y) * SIN30;
}

void	renderer_project_orhtographic(t_vec3 *const vec,
		const int32_t scale_factor)
{
	vec->x = vec->x * scale_factor;
	vec->y = vec->y * scale_factor;
}

void	renderer_world_project(t_renderer *const self, const int32_t width,
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
			if (self->projection == PROJECTION_ISO)
				renderer_project_isometric(&self->world[y][x++]);
			else if (self->projection == PROJECTION_ORT)
				renderer_project_orhtographic(&self->world[y][x++],
					self->scale_factor);
		}
		++y;
	}
}
