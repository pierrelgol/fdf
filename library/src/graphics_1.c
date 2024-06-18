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

t_vec2 vec2(const int32_t x, const int32_t y)
{
	return (t_vec2){
	    .x = x,
	    .y = y,
	};
}

t_vec2 vec2_add(const t_vec2 a, const t_vec2 b)
{
	return (t_vec2){
	    .x = a.x + b.x,
	    .y = a.y + b.y,
	};
}

t_vec2 vec2_sub(const t_vec2 a, const t_vec2 b)
{
	return (t_vec2){
	    .x = a.x - b.x,
	    .y = a.y - b.y,
	};
}

t_vec2 vec2_mul(const t_vec2 a, const t_vec2 b)
{
	return (t_vec2){
	    .x = a.x * b.x,
	    .y = a.y * b.y,
	};
	
}

t_vec2 vec2_div(const t_vec2 a, const t_vec2 b)
{
	return (t_vec2){
	    .x = a.x * b.x,
	    .y = a.y * b.y,
	};
}
