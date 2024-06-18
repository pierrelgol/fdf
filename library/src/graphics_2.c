/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:11:11 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 08:11:11 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_vec2	vec2_add(const t_vec2 v0, const t_vec2 v1)
{
	return (vec2(v0.x + v1.x, v0.y + v1.y));
}

t_vec2	vec2_sub(const t_vec2 v0, const t_vec2 v1)
{
	return (vec2(v0.x - v1.x, v0.y - v1.y));
}

t_vec2	vec2_mul(const t_vec2 v0, const t_vec2 v1)
{
	return (vec2(v0.x * v1.x, v0.y * v1.y));
}

t_vec2	vec2_div(const t_vec2 v0, const t_vec2 v1)
{
	return (vec2(v0.x / v1.x, v0.y / v1.y));
}

t_vec2	vec2_scale(const t_vec2 v, const int32_t scale)
{
	return (vec2(v.x * scale, v.y * scale));
}
