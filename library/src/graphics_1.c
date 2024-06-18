/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:11:26 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 08:11:27 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_vec2	vec2(const int32_t x, const int32_t y)
{
	return ((t_vec2){
		.x = x,
		.y = y,
	});
}

t_vec3	vec3(const int32_t x, const int32_t y, const int32_t z)
{
	return ((t_vec3){
		.x = x,
		.y = y,
		.z = z,
	});
}

t_vec4	vec4(const int32_t x, const int32_t y, const int32_t z, const int32_t w)
{
	return ((t_vec4){
		.x = x,
		.y = y,
		.z = z,
		.w = w,
	});
}

t_mat4	mat4(const t_vec4 r0, const t_vec4 r1, const t_vec4 r2, const t_vec4 r3)
{
	return ((t_mat4){
		.data[0] = r0.x,
		.data[1] = r0.y,
		.data[2] = r0.z,
		.data[3] = r0.w,
		.data[4] = r1.x,
		.data[5] = r1.y,
		.data[6] = r1.z,
		.data[7] = r1.w,
		.data[8] = r2.x,
		.data[9] = r2.y,
		.data[10] = r2.z,
		.data[11] = r2.w,
		.data[12] = r3.x,
		.data[13] = r3.y,
		.data[14] = r3.z,
		.data[15] = r3.w,
	});
}

t_color	color(const int32_t value)
{
	return ((t_color){
		.a = (value >> 24) & 0xFF,
		.r = (value >> 16) & 0xFF,
		.g = (value >> 8) & 0xFF,
		.b = (value) & 0xFF,
	});
}
