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

int32_t inputs_movement(const int32_t keycode, t_camera *const camera)
{
	if (keycode == 65361)
		camera_update_position(camera, vec3(-MOVE_STEP, 0, 0));
	else if (keycode == 65363)
		camera_update_position(camera, vec3(MOVE_STEP, 0, 0));
	else if (keycode == 65362)
		camera_update_position(camera, vec3(0, -MOVE_STEP, 0));
	else if (keycode == 65364)
		camera_update_position(camera, vec3(0, MOVE_STEP, 0));
	else if (keycode == 45)
		camera_update_zoom(camera, -ZOOM_STEP);
	else if (keycode == 61)
		camera_update_zoom(camera, ZOOM_STEP);
	else
		return (false);
	return (true);
}

int32_t inputs_rotation(const int32_t keycode, t_camera *const camera)
{
	if (keycode == 113)
		camera_update_rotation(camera, vec3(-ROTA_STEP, 0, 0));
	else if (keycode == 101)
		camera_update_rotation(camera, vec3(ROTA_STEP, 0, 0));
	else if (keycode == 119)
		camera_update_rotation(camera, vec3(0, -ROTA_STEP, 0));
	else if (keycode == 115)
		camera_update_rotation(camera, vec3(0, ROTA_STEP, 0));
	else if (keycode == 97)
		camera_update_rotation(camera, vec3(0, 0, -ROTA_STEP));
	else if (keycode == 100)
		camera_update_rotation(camera, vec3(0, 0, ROTA_STEP));
	else
		return (false);
	return (true);
}

int32_t inputs_params(const int32_t keycode, t_camera *const camera)
{
	if (keycode == 91)
		camera_update_zoom(camera, -ZOOM_STEP);
	else if (keycode == 93)
		camera_update_zoom(camera, +ZOOM_STEP);
	else if (keycode == 106)
		camera_update_amplitude(camera, -ZAMP_STEP);
	else if (keycode == 107)
		camera_update_amplitude(camera, ZAMP_STEP);
	else
		return (false);
	return (true);
}

int32_t inputs_on_key_press(const int32_t keycode, void *const handle)
{
	t_fdf_container *self;

	self = (t_fdf_container *) handle;
	printf("keycode :%d\n", keycode);
	if (keycode == XK_Escape)
		inputs_on_program_exit(handle);
	if (inputs_movement(keycode, self->camera))
		fdf_container_run(self);
	else if (inputs_rotation(keycode, self->camera))
		fdf_container_run(self);
	else if (inputs_params(keycode, self->camera))
		fdf_container_run(self);
	else
		return (0);
	return (1);
}
