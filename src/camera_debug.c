/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:42:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 16:42:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	vec3_print(const char *label, const t_vec3 vec)
{
	printf("%s : {%f, %f, %f}\n", label, vec.x, vec.y, vec.z);
}

void	camera_print(const t_camera *const self)
{
	printf("--------------------------------\n");
	printf("CAMERA :\n");
	vec3_print("self->position", self->position);
	vec3_print("self->rotation", self->rotation);
	printf("self->zoom : %.6f\n", self->zoom);
	printf("self->amplitude : %.6f\n", self->amplitude);
}
