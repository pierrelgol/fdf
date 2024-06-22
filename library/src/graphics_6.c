/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:11:46 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 08:11:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int32_t	color_value(const t_color col)
{
	return (col.color);
}

float_t	vec2per(const t_vec2 start, const t_vec2 end, const t_vec2 at)
{
	float_t	total_distance;
	float_t	curr_distance;

	total_distance = vec2_distance(start, end);
	curr_distance = vec2_distance(start, at);
	if (total_distance == 0.0f)
		return (0.0f);
	return (curr_distance / total_distance);
}

float_t	vec3_percentage(const t_vec3 start, const t_vec3 end, const t_vec3 at)
{
	float_t	total_distance;
	float_t	curr_distance;

	total_distance = vec3_distance(start, end);
	curr_distance = vec3_distance(start, at);
	if (total_distance == 0.0f)
		return (0.0f);
	return (curr_distance / total_distance);
}

float	fclamp(float min, float value, float max)
{
	return (fmaxf(min, fminf(value, max)));
}

t_color	lerp(const t_color start, const t_color end, const float_t scalar)
{
	t_color	lerped_color;
	float_t	t;

	t = fclamp(0.0f, scalar, 1.0f);
	lerped_color.a = (uint8_t)(start.a + (end.a - start.a) * t);
	lerped_color.r = (uint8_t)(start.r + (end.r - start.r) * t);
	lerped_color.g = (uint8_t)(start.g + (end.g - start.g) * t);
	lerped_color.b = (uint8_t)(start.b + (end.b - start.b) * t);
	return (lerped_color);
}
