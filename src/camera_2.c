/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:45:36 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:45:36 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

t_vec3    camera_get_position(const t_camera *const self)
{
	return (self->position);
}

t_vec3    camera_get_rotation(const t_camera *const self)
{
	return (self->rotation);
}

t_vec3    camera_get_zoom(const t_camera *const self)
{
	return (vec3(self->zoom, self->zoom, self->zoom));
}

t_vec3    camera_get_amplitude(const t_camera *const self)
{
	return (vec3(1, 1, self->amplitude));
}

t_camera *camera_destroy(t_camera *const self)
{
	if (self)
		memory_dealloc(self);
	return (NULL);
}

