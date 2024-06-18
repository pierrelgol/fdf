/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:11:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 08:11:43 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_mat4	mat4_identity(void)
{
	return (mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0,
				0, 0, 1)));
}

float_t	vec2_distance(const t_vec2 v1, const t_vec2 v2)
{
	const float_t	dx = v2.x - v1.x;
	const float_t	dy = v2.y - v1.y;

	return (sqrt(dx * dx + dy * dy));
}

float_t	vec3_distance(const t_vec3 v1, const t_vec3 v2)
{
	const float_t	dx = v2.x - v1.x;
	const float_t	dy = v2.y - v1.y;
	const float_t	dz = v2.z - v1.z;

	return (sqrt(dx * dx + dy * dy + dz * dz));
}
