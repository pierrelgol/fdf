/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 08:19:44 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/16 08:19:45 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t inputs_on_program_exit(void *const handle)
{
	fdf_container_destroy(handle);
	return (false);
}

int32_t inputs_on_key_press(const int32_t keycode, void *const handle)
{
	t_fdf_container *self;

	printf("keycode :%d\n", keycode);
	self = (t_fdf_container *) handle;
	if (keycode == XK_Escape)
		inputs_on_program_exit(handle);
	if (keycode == 65361) // left
		self->renderer->offset_x -= 10;
	if (keycode == 65363) // right
		self->renderer->offset_x += 10;
	if (keycode == 65362) // up
		self->renderer->offset_y -= 10;
	if (keycode == 65364) // down
		self->renderer->offset_y += 10;
	if (keycode == 45) // forward
		self->renderer->offset_z -= 10;
	if (keycode == 61) // backward
		self->renderer->offset_z += 10;
	if (keycode == 113)
		self->renderer->offset_pitch -= 0.1f;
	if (keycode == 101)
		self->renderer->offset_pitch += 0.1f;
	if (keycode == 119)
		self->renderer->offset_yawn -= 0.1f;
	if (keycode == 115)
		self->renderer->offset_yawn += 0.1f;
	if (keycode == 97)
		self->renderer->offset_roll -= 0.1f;
	if (keycode == 100)
		self->renderer->offset_roll += 0.1f;
	if (keycode == 91)
	{
		if (self->renderer->offset_zoom >= 0.1f)
			self->renderer->offset_zoom -= 0.1f;
	}
	if (keycode == 93)
	{
		if (self->renderer->offset_zoom < 100.0f)
			self->renderer->offset_zoom += 0.1f;
	}
	if (keycode == 106)
	{
		if (self->renderer->z_amplitude >= -10.0f)
			self->renderer->z_amplitude -= 0.1f;
	}
	if (keycode == 107)
	{
		if (self->renderer->z_amplitude < 100.0f)
			self->renderer->z_amplitude += 0.1f;
	}

	fdf_container_run(self);
	return (0);
}
