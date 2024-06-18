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

int32_t inputs_movement(const int32_t keycode, void *const handle)
{
	t_fdf_container *self;

	self = (t_fdf_container *) handle;
	if (keycode == 65361)
		self->renderer->position.x -= 10;
	else if (keycode == 65363)
		self->renderer->position.x += 10;
	else if (keycode == 65362)
		self->renderer->position.y -= 10;
	else if (keycode == 65364)
		self->renderer->position.y += 10;
	else if (keycode == 45)
		self->renderer->position.z -= 10;
	else if (keycode == 61)
		self->renderer->position.z += 10;
	else
		return (false);
	return (true);
}

int32_t inputs_rotation(const int32_t keycode, void *const handle)
{
	t_fdf_container *self;
	t_vec3	*o;

	self = (t_fdf_container *) handle;
	o = &self->renderer->orientation;
	if (keycode == 113)
		o->x = ((o->x + 1) % 100);
	else if (keycode == 101)
		o->x = ((o->x - 1) % 100);
	else if (keycode == 119)
		o->y = ((o->y + 1) % 100);
	else if (keycode == 115)
		o->y = ((o->y - 1) % 100);
	else if (keycode == 97)
		o->z = ((o->z - 1) % 100);
	else if (keycode == 100)
		o->z = ((o->z - 1) % 100);
	else
		return (false);
	return (true);
}

int32_t inputs_params(const int32_t keycode, void *const handle)
{
	t_fdf_container *self;

	self = (t_fdf_container *) handle;
	if (keycode == 91 && self->renderer->offset_zoom >= 0.1f)
		self->renderer->offset_zoom -= 0.1f;
	else if (keycode == 93 && self->renderer->offset_zoom < 100.0f)
		self->renderer->offset_zoom += 0.1f;
	else if (keycode == 106 && self->renderer->z_amplitude >= -10.0f)
		self->renderer->z_amplitude -= 0.1f;
	else if (keycode == 107 && self->renderer->z_amplitude < 100.0f)
		self->renderer->z_amplitude += 0.1f;
	else
		return (0);
	return (1);
}

int32_t inputs_on_key_press(const int32_t keycode, void *const handle)
{
	t_fdf_container *self;

	self = (t_fdf_container *) handle;
	printf("keycode :%d\n", keycode);
	if (keycode == XK_Escape)
		inputs_on_program_exit(handle);
	if (inputs_movement(keycode, handle))
		fdf_container_run(self);
	else if (inputs_rotation(keycode, handle))
		fdf_container_run(self);
	else if (inputs_params(keycode, handle))
		fdf_container_run(self);
	else
		return (0);
	return (1);
}
