/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_draw_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:48:27 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 09:48:27 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate(double *const a, double *const b, const double cos_angle,
		const double sin_angle)
{
	double	temp_a;

	temp_a = *a * cos_angle - *b * sin_angle;
	*b = *a * sin_angle + *b * cos_angle;
	*a = temp_a;
}

void	initialize_renderer_values(t_renderer *self)
{
	self->cos_pitch = cos(self->offset_pitch);
	self->sin_pitch = sin(self->offset_pitch);
	self->cos_yaw = cos(self->offset_yaw);
	self->sin_yaw = sin(self->offset_yaw);
	self->cos_roll = cos(self->offset_roll);
	self->sin_roll = sin(self->offset_roll);
	self->zoom = self->offset_zoom;
	self->scale_factor = (2 * ((double)self->ratio_w / self->ratio_w))
		* self->zoom;
	self->normalized_x = 0.0;
	self->normalized_y = 0.0;
	self->screen_x = 0.0;
	self->screen_y = 0.0;
	self->projected_x = 0.0;
	self->projected_y = 0.0;
	self->relative_x = 0.0;
	self->relative_y = 0.0;
	self->relative_z = 0.0;
}

void	project_to_screen(t_renderer *self, double cos30, double sin30)
{
	self->projected_x = (self->relative_x - self->relative_y) * cos30;
	self->projected_y = (self->relative_x + self->relative_y) * sin30
		- self->relative_z;
	self->screen_x = self->projected_x * self->scale_factor;
	self->screen_y = self->projected_y * self->scale_factor;
}


void	renderer_offset_world_pos(t_renderer *const self,
		const int32_t world_width, const int32_t world_height)
{
	int32_t	y;
	int32_t	x;

	y = 0;
	while (y < world_height)
	{
		x = 0;
		while (x < world_width)
		{
			self->world_coord[y][x].x += self->offset_x;
			self->world_coord[y][x].y += self->offset_y;
			self->world_coord[y][x].z += (self->p.z + self->offset_z)
				* self->z_amplitude;
			++x;
		}
		++y;
	}
}