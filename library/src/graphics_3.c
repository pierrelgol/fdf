/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:11:18 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 08:11:19 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_vec3	vec3_add(const t_vec3 v0, const t_vec3 v1)
{
	return (vec3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z));
}

t_vec3	vec3_sub(const t_vec3 v0, const t_vec3 v1)
{
	return (vec3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z));
}

t_vec3	vec3_mul(const t_vec3 v0, const t_vec3 v1)
{
	return (vec3(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z));
}

t_vec3	vec3_div(const t_vec3 v0, const t_vec3 v1)
{
	return (vec3(v0.x / v1.x, v0.y / v1.y, v0.z * v1.z));
}

t_vec3	vec3_scale(const t_vec3 v, const int32_t scale)
{
	return (vec3(v.x * scale, v.y * scale, v.z * scale));
}
