/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:55:41 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 10:55:42 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	renderer_compute_constants(t_renderer *self)
{
	t_camera	*camera;

	camera = self->camera;
	if (self->projection == PROJECTION_ISO)
		self->scale_factor = (((float_t)WIDTH / HEIGHT) * self->camera->zoom)
			* ((float_t)9 / 21);
	else if (self->projection == PROJECTION_ORT)
		self->scale_factor = ((float_t)WIDTH / HEIGHT) * self->camera->zoom;
	camera->cos_pitch = cos(camera->rad_pitch);
	camera->sin_pitch = sin(camera->rad_pitch);
	camera->cos_yaw = cos(camera->rad_yaw);
	camera->sin_yaw = sin(camera->rad_yaw);
	camera->cos_roll = cos(camera->rad_roll);
	camera->sin_roll = sin(camera->rad_roll);
	self->screen_center = self->map->screen_center;
}

void	renderer_start(t_renderer *const self, const int32_t world_width,
		const int32_t world_height)
{
	renderer_compute_constants(self);
	renderer_world_translate(self, world_width, world_height);
	renderer_world_rotate(self, world_width, world_height);
	renderer_world_project(self, world_width, world_height);
	renderer_world_fill(self, world_width, world_height);
}
