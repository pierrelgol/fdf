/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:45:25 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:45:25 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_camera *camera_create(const t_vec3 position, const t_vec3 rotation, const float_t zoom, const float_t amplitude)
{
	t_camera *self;

	self = memory_alloc(sizeof(t_camera));
	if (!self)
		return (NULL);
	self->position = position;
	self->rotation = rotation;
	self->zoom = zoom;
	self->amplitude = amplitude;
	return (self);
}

void camera_update_position(t_camera *const self, const t_vec3 position_offset)
{
	self->position = vec3_add(self->position, position_offset);
}

void camera_update_rotation(t_camera *const self, const t_vec3 rotation_offset)
{
	self->rotation = vec3_add(self->rotation, rotation_offset);
}

void camera_update_zoom(t_camera *const self, const float_t zoom_offset)
{
	self->zoom += zoom_offset;
}

void camera_update_amplitude(t_camera *const self, const float_t amplitude_offset)
{
	self->amplitude += amplitude_offset;
}