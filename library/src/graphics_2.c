/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:06:07 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:06:07 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

float vec2_length(const t_vec2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float vec2_length_squared(const t_vec2 v)
{
	return v.x * v.x + v.y * v.y;
}

t_vec2 vec2_normalize(t_vec2 v)
{
	vec2_normalized(&v);
	return (v);
}

void vec2_normalized(t_vec2 *const v)
{
	float len = vec2_length(*v);
	if (len != 0.0f)
	{
		float inv_len = 1.0f / len;
		v->x *= inv_len;
		v->y *= inv_len;
	}
}
