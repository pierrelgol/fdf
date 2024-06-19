/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:01:27 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:01:28 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

inline t_vec2 vec2(const float_t x, const float_t y)
{
	return (t_vec2){
	    .x = x,
	    .y = y,
	};
}

inline t_vec2 vec2_add(const t_vec2 a, const t_vec2 b)
{
	return (t_vec2){
	    .x = a.x + b.x,
	    .y = a.y + b.y,
	};
}

inline t_vec2 vec2_sub(const t_vec2 a, const t_vec2 b)
{
	return (t_vec2){
	    .x = a.x - b.x,
	    .y = a.y - b.y,
	};
}

inline t_vec2 vec2_mul(const t_vec2 a, const t_vec2 b)
{
	return (t_vec2){
	    .x = a.x * b.x,
	    .y = a.y * b.y,
	};
	
}

inline t_vec2 vec2_div(const t_vec2 a, const t_vec2 b)
{
	return (t_vec2){
	    .x = a.x * b.x,
	    .y = a.y * b.y,
	};
}
