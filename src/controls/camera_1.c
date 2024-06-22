/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:20:29 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/22 11:20:30 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_camera	*camera_create(const t_vec3 pos, const t_vec3 rot,
		const float_t zoom, const float_t z_scale)
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

t_camera	*camera_destroy(t_camera *const self)
{
	if (self)
		memory_dealloc(self);
	return (NULL);
}
