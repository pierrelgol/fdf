/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:10:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/20 11:10:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define COS30 0.86602540378f
#define SIN30 0.49999999999f

void renderer_rendering_start(t_renderer *const self, const int32_t width, const int32_t height)
{
	initialize_renderer_values(self);
	renderer_offset_world_pos(self, width, height);
	renderer_render(self, width, height);
}

void initialize_renderer_values(t_renderer *self)
{
	t_camera	*camera;

	camera = self->camera;
	self->scale_factor = ((double) self->ratio_w / self->ratio_w) * self->camera->zoom;
	self->screen_x = 0.0;
	self->screen_y = 0.0;
	self->projected_x = 0.0;
	self->projected_y = 0.0;
	self->relative_x = 0.0;
	self->relative_y = 0.0;
	self->relative_z = 0.0;
	camera->cos_pitch = cos(camera->rad_pitch);
	camera->sin_pitch = sin(camera->rad_pitch);
	camera->cos_yaw = cos(camera->rad_yaw);
	camera->sin_yaw = sin(camera->rad_yaw);
	camera->cos_roll = cos(camera->rad_roll);
	camera->sin_roll = sin(camera->rad_roll);
}

void renderer_offset_world_pos(t_renderer *const self, const int32_t world_width, const int32_t world_height)
{
	int32_t y;
	int32_t x;

	y = 0;
	while (y < world_height)
	{
		x = 0;
		while (x < world_width)
		{
			self->world_coord[y][x] =
			    vec3_add(self->world_coord[y][x], self->camera->cam_position);
			self->world_coord[y][x].z *= (1 * self->camera->z_scale);
			++x;
		}
		++y;
	}
}

void renderer_render(t_renderer *const self, const int32_t world_width, const int32_t world_height)
{
	int32_t x;
	int32_t y;

	y = 0;
	while (y < world_height)
	{
		x = 0;
		while (x < world_width)
		{
			renderer_fill_relative(self, x, y);
			rotate(&self->relative_x, &self->relative_z, self->camera->cos_yaw,
			       self->camera->sin_yaw);
			rotate(&self->relative_y, &self->relative_z, self->camera->cos_pitch,
			       self->camera->sin_pitch);
			rotate(&self->relative_x, &self->relative_y, self->camera->cos_roll,
			       self->camera->sin_roll);
			project_to_screen(self, COS30, SIN30);
			self->screen_coord[y][x] = (t_vec2){{self->screen_x, self->screen_y}};
			self->screen_color[y][x] = self->world_color[y][x];
			++x;
		}
		++y;
	}
	screen_print(self->screen_coord, world_width, world_height);
}

void renderer_fill_relative(t_renderer *const self, const int32_t x, const int32_t y)
{
	t_vec3 v;

	v = self->world_coord[y][x];
	self->relative_x = v.x / self->ratio_w;
	self->relative_y = v.y / self->ratio_h;
	self->relative_z = v.z / self->camera->zoom;
}

void rotate(double *const a, double *const b, const double cos_angle, const double sin_angle)
{
	double temp_a;

	temp_a = *a * cos_angle - *b * sin_angle;
	*b = *a * sin_angle + *b * cos_angle;
	*a = temp_a;
}

void project_to_screen(t_renderer *self, double cos30, double sin30)
{
	self->projected_x = (self->relative_x - self->relative_y) * cos30;
	self->projected_y = (self->relative_x + self->relative_y) * sin30 - self->relative_z;
	self->screen_x = self->projected_x * self->scale_factor;
	self->screen_y = self->projected_y * self->scale_factor;
}
