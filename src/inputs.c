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
	if (keycode == XK_h)
		camera_move(camera, vec3(-MOVE_STEP, 0, 0));
	else if (keycode == XK_l)
		camera_move(camera, vec3(MOVE_STEP, 0, 0));
	else if (keycode == XK_j)
		camera_move(camera, vec3(0, -MOVE_STEP, 0));
	else if (keycode == XK_k)
		camera_move(camera, vec3(0, MOVE_STEP, 0));
	else if (keycode == XK_p)
		camera_move(camera, vec3(0, 0, -MOVE_STEP));
	else if (keycode == XK_n)
		camera_move(camera, vec3(0, 0, MOVE_STEP));
	else
		return (false);
	return (true);
}

int32_t inputs_rotation(const int32_t keycode, t_camera *const camera)
{
	if (keycode == XK_w)
		camera_rota(camera, vec3(ROTA_STEP, 0, 0));
	else if (keycode == XK_s)
		camera_rota(camera, vec3(-ROTA_STEP, 0, 0));
	else if (keycode == XK_a)
		camera_rota(camera, vec3(0, -ROTA_STEP, 0));
	else if (keycode == XK_d)
		camera_rota(camera, vec3(0, ROTA_STEP, 0));
	else if (keycode == XK_q)
		camera_rota(camera, vec3(0, 0, -ROTA_STEP));
	else if (keycode == XK_e)
		camera_rota(camera, vec3(0, 0, ROTA_STEP));
	else
		return (false);
	return (true);
}

int32_t inputs_params(const int32_t keycode, t_camera *const camera)
{
	if (keycode == XK_minus)
		camera_zoom(camera, ZOOM_STEP);
	else if (keycode == XK_plus)
		camera_zoom(camera, -ZOOM_STEP);
	if (keycode == XK_i)
		camera->projection = PROJECTION_ISO;
	if (keycode == XK_o)
		camera->projection = PROJECTION_ORT;
	return (1);
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
