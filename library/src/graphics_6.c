/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:20:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:20:15 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_color color(const int32_t argb)
{
	return (t_color){
	    .a = (argb >> 24) & 0xFF,
	    .r = (argb >> 16) & 0xFF,
	    .g = (argb >> 8) & 0xFF,
	    .b = (argb) & 0xFF,
	};
}

int32_t color2_lerp(t_vec2 at, t_vec2 start, t_vec2 end, const t_color2 start_end)
{
	const int32_t start_color = start_end.argb[0];
	const int32_t end_color = start_end.argb[1];
	const float_t alpha = (at.x - start.x) / (end.x - start.x);

	const t_color result = (t_color){
	    .a = (1.0f - alpha) * ((start_color >> 24) & 0xFF) + alpha * ((end_color >> 24) & 0xFF),
	    .r = (1.0f - alpha) * ((start_color >> 16) & 0xFF) + alpha * ((end_color >> 16) & 0xFF),
	    .g = (1.0f - alpha) * ((start_color >> 8) & 0xFF) + alpha * ((end_color >> 8) & 0xFF),
	    .b = (1.0f - alpha) * (start_color & 0xFF) + alpha * (end_color & 0xFF),
	};
	return (result.argb);
}

t_color2 color2(const int32_t argb1, const int32_t argb2)
{
	t_color2 result;
	result.argb[0] = argb1;
	result.argb[1] = argb2;
	return (result);
}
