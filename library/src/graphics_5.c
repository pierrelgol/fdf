/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:19:30 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:19:31 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void vec3_normalized(t_vec3 *v)
{
	float len = vec3_length(*v);
	if (len != 0.0f)
	{
		float inv_len = 1.0f / len;
		v->x *= inv_len;
		v->y *= inv_len;
		v->z *= inv_len;
	}
}

t_vec3 vec3_rotate_x(t_vec3 v, float angle)
{
	const float cos_a = cos(angle);
	const float sin_a = sin(angle);
	return (vec3(v.x, v.y * cos_a - v.z * sin_a, v.y * sin_a + v.z * cos_a));
}

t_vec3 vec3_rotate_y(t_vec3 v, float angle)
{
	const float cos_a = cos(angle);
	const float sin_a = sin(angle);
	return (vec3(v.x * cos_a + v.z * sin_a, v.y, -v.x * sin_a + v.z * cos_a));
}

t_vec3 vec3_rotate_z(t_vec3 v, float angle)
{
	const float cos_a = cos(angle);
	const float sin_a = sin(angle);
	return (vec3(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a, v.z));
}
