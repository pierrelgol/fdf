/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:12:26 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:12:26 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

#include <math.h>

float vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec3_distance(t_vec3 a, t_vec3 b)
{
	const float dx = b.x - a.x;
	const float dy = b.y - a.y;
	const float dz = b.z - a.z;

	return (sqrt(dx * dx + dy * dy + dz * dz));
}

float vec3_distance_squared(t_vec3 a, t_vec3 b)
{
	const float dx = b.x - a.x;
	const float dy = b.y - a.y;
	const float dz = b.z - a.z;
	return (dx * dx + dy * dy + dz * dz);
}

t_vec3 vec3_normalize(t_vec3 v)
{
	vec3_normalized(&v);
	return (v);
}
