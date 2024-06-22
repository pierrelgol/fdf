/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_translate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:55:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 11:55:15 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	renderer_apply_camera_zoom_and_scale(t_vec3 *vec, t_camera *camera)
{
	vec->x *= camera->zoom;
	vec->y *= camera->zoom;
	vec->z *= camera->zoom;
	vec->z *= camera->z_scale;
}

void	renderer_world_translate(t_renderer *const self, const int32_t width,
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
			renderer_apply_camera_zoom_and_scale(&self->world[y][x],
				self->camera);
			self->world[y][x].x += self->camera->cam_position.x;
			self->world[y][x].y += self->camera->cam_position.y;
			self->world[y][x].z += self->camera->cam_position.z;
			++x;
		}
		++y;
	}
}
