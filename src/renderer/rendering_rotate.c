/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:55:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 11:55:07 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void renderer_rotate_vec(t_vec3 *const vec, t_camera *const camera)
{
	double temp_x = vec->x;
	double temp_y = vec->y;

	// Apply rotations in the order: pitch, yaw, roll
	// Rotate around X-axis (pitch)
	vec->y = temp_y * camera->cos_pitch - vec->z * camera->sin_pitch;
	vec->z = temp_y * camera->sin_pitch + vec->z * camera->cos_pitch;

	temp_y = vec->y;

	// Rotate around Y-axis (yaw)
	vec->x = temp_x * camera->cos_yaw + vec->z * camera->sin_yaw;
	vec->z = -temp_x * camera->sin_yaw + vec->z * camera->cos_yaw;

	temp_x = vec->x;

	// Rotate around Z-axis (roll)
	vec->x = temp_x * camera->cos_roll - temp_y * camera->sin_roll;
	vec->y = temp_x * camera->sin_roll + temp_y * camera->cos_roll;
}


void renderer_world_rotate(t_renderer *const self, const int32_t width, const int32_t height)
{
	int32_t y;
	int32_t x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
			renderer_rotate_vec(&self->world[y][x++], self->camera);
		++y;
	}
}
