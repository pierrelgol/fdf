/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:20:34 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/22 11:20:35 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	camera_move(t_camera *const self, t_vec3 offset)
{
	self->cam_position = vec3_add(self->cam_position, offset);
}

void	camera_rota(t_camera *const self, t_vec3 offset)
{
	self->deg_pitch += offset.x;
	self->deg_yaw += offset.y;
	self->deg_roll += offset.z;
	self->rad_pitch = (self->deg_pitch * M_PI / 180.0f);
	self->rad_yaw = (self->deg_yaw * M_PI / 180.0f);
	self->rad_roll = (self->deg_roll * M_PI / 180.0f);
}

void	camera_zoom(t_camera *const self, float_t offset)
{
	self->zoom += offset;
}

void	camera_scale(t_camera *const self, float_t offset)
{
	self->z_scale += offset;
}
