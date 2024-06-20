/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 08:19:46 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/14 08:19:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int32_t char_to_digit(const char ch)
{
	if (ch >= '0' && ch <= '9')
		return (ch - '0');
	else if (ch >= 'A' && ch <= 'F')
		return (ch - 'A' + 10);
	else if (ch >= 'a' && ch <= 'f')
		return (ch - 'a' + 10);
	return (0);
}

int64_t string_to_base(const char *str, char **endptr, const int32_t base)
{
	int64_t result;
	bool    negative;

	negative = false;
	while (is_space(*str))
		++str;
	if (*str == '-' || *str == '+')
	{
		negative = true;
		++str;
	}
	if (base == 16)
		str += 3;
	result = 0;
	while (is_hex(*str))
		result = (char_to_digit(*str++)) + (result * base);
	if (*str == '\0')
		*endptr = NULL;
	else
		*endptr = (char *) str;
	return (((negative) * (-result)) + ((!negative) * (result)));
}

t_color color_lerp(float_t total_distance, float_t point_distance, t_color color_start, t_color color_end)
{
	t_color result;
	float   t;

	t = point_distance / total_distance;
	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
	result.a = (uint8_t) ((1 - t) * color_start.a + t * color_end.a);
	result.r = (uint8_t) ((1 - t) * color_start.r + t * color_end.r);
	result.g = (uint8_t) ((1 - t) * color_start.g + t * color_end.g);
	result.b = (uint8_t) ((1 - t) * color_start.b + t * color_end.b);
	return (result);
}

void screen_print(t_vec2 **coord, int32_t width, int32_t height)
{
	int32_t x;
	int32_t y;
	t_vec2  p;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			p = coord[y][x];
			printf("{%3d,%3d}", p.x, p.y);
			++x;
		}
		printf("\n");
		++y;
	}
}

void world_print(t_vec3 **coord, int32_t width, int32_t height)
{
	int32_t x;
	int32_t y;
	t_vec3  p;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			p = coord[y][x];
			printf("{%3d,%3d,%3d}", p.x, p.y, p.z);
			++x;
		}
		printf("\n");
		++y;
	}
}
