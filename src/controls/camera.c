/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:31:41 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/20 11:31:41 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_camera *camera_create(const t_vec3 pos, const t_vec3 rot, const float_t zoom, const float_t z_scale)
{
	t_camera	*self;

	self = memory_alloc(sizeof(t_camera));
	if (!self)
		return (NULL);
	self->cam_position = pos;
	self->deg_pitch = rot.x;
	self->deg_yaw = rot.y;
	self->deg_roll = rot.z;
	self->rad_pitch = (self->deg_pitch * M_PI / 180.0f);
	self->rad_yaw = (self->deg_yaw * M_PI / 180.0f);
	self->rad_roll = (self->deg_roll * M_PI / 180.0f);
	self->zoom = zoom;
	self->z_scale = z_scale;
	return (self);
}

void      camera_move(t_camera *const self, t_vec3 offset)
{
	self->cam_position = vec3_add(self->cam_position, offset);
}

void      camera_rota(t_camera *const self, t_vec3 offset)
{
	self->deg_pitch += offset.x;
	self->deg_yaw += offset.y;
	self->deg_roll += offset.z;
	self->rad_pitch = (self->deg_pitch * M_PI / 180.0f);
	self->rad_yaw = (self->deg_yaw * M_PI / 180.0f);
	self->rad_roll = (self->deg_roll * M_PI / 180.0f);
}

void      camera_zoom(t_camera *const self, float_t offset)
{
	self->zoom += offset;
}

void      camera_scale(t_camera *const self, float_t offset)
{
	self->z_scale += offset;
}

t_camera *camera_destroy(t_camera *const self)
{
	if (self)
		memory_dealloc(self);
	return (NULL);
}
