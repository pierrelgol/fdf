/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:09:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:09:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_vec3 vec3(const int32_t x, const int32_t y, const int32_t z)
{
	return (t_vec3){
	    .x = x,
	    .y = y,
	    .z = z,
	};
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
	return (t_vec3){
	    .x = a.x + b.x,
	    .y = a.y + b.y,
	    .z = a.z + b.z,
	};
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
	return (t_vec3){
	    .x = a.x - b.x,
	    .y = a.y - b.y,
	    .z = a.z - b.z,
	};
}

t_vec3 vec3_mul(t_vec3 a, t_vec3 b)
{
	return (t_vec3){
	    .x = a.x * b.x,
	    .y = a.y * b.y,
	    .z = a.z * b.z,
	};
}

t_vec3 vec3_div(t_vec3 a, t_vec3 b)
{
	return (t_vec3){
	    .x = a.x / b.x,
	    .y = a.y / b.y,
	    .z = a.z / b.z,
	};
}
