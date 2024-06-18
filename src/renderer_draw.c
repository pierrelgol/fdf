/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:10:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/16 11:10:07 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	renderer_setup(t_renderer *const self, const t_fdf_container *const fdf)
{
	self->mlx_handle = fdf->mlx_handle;
	self->win_handle = fdf->win_handle;
	self->img_handle = fdf->img_handle;
	self->img_buffer = fdf->img_buffer;
	self->img_endian = fdf->img_endian;
	self->img_size = fdf->img_size;
	self->img_bpp = fdf->img_bpp;
	self->ratio_h = ((float_t)self->screen_height / self->world_height);
	self->ratio_w = ((float_t)self->screen_width / self->world_width);
	initialize_renderer_values(self);
	renderer_offset_world_pos(self, self->world_width, self->world_height);
	renderer_from_world_to_projected(self, self->world_width,
		self->world_height);
}

void	renderer_fill_relative(t_renderer *const self, const int32_t x,
		const int32_t y)
{
	t_vec3	v;

	v = self->world_coord[y][x];
	self->relative_x = v.x / self->ratio_w;
	self->relative_y = v.y / self->ratio_h;
	self->relative_z = v.z / self->zoom;
}

#define COS30 0.86602540378f
#define SIN30 0.49999999999f

void	renderer_from_world_to_projected(t_renderer *const self,
		const int32_t world_width, const int32_t world_height)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (y < world_height)
	{
		x = 0;
		while (x < world_width)
		{
			renderer_fill_relative(self, x, y);
			rotate(&self->relative_x, &self->relative_z, self->cos_yaw,
				self->sin_yaw);
			rotate(&self->relative_y, &self->relative_z, self->cos_pitch,
				self->sin_pitch);
			rotate(&self->relative_x, &self->relative_y, self->cos_roll,
				self->sin_roll);
			project_to_screen(self, COS30, SIN30);
			self->screen_coord[y][x] = (t_vec2){{self->screen_x,
				self->screen_y}};
			self->screen_color[y][x] = self->world_color[y][x];
			++x;
		}
		++y;
	}
}
