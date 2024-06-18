/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:11:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 08:11:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_vec4	vec4_add(const t_vec4 v0, const t_vec4 v1)
{
	return (vec4(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w));
}

t_vec4	vec4_sub(const t_vec4 v0, const t_vec4 v1)
{
	return (vec4(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w));
}

t_vec4	vec4_mul(const t_vec4 v0, const t_vec4 v1)
{
	return (vec4(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w));
}

t_vec4	vec4_div(const t_vec4 v0, const t_vec4 v1)
{
	return (vec4(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w));
}

t_vec4	vec4_scale(const t_vec4 v, const int32_t scale)
{
	return (vec4(v.x * scale, v.y * scale, v.z * scale, v.w * scale));
}
