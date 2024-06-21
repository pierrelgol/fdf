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

int32_t base10_to_integer(const char *const string)
{
	int32_t result;
	int32_t index;
	int32_t sign;

	if (!string)
		return (0);
	index = 0;
	sign = 1;
	while (string[index] && is_space(string[index]))
		++index;
	if (string[index] && ((string[index] == '-') || (string[index] == '+')))
	{
		if (string[index] == '-' && ++index)
			sign = -1;
	}
	result = 0;
	while (string[index] && is_digit(string[index]))
		result = (string[index++] - '0') + (result * 10);
	return (result * sign);
}

int32_t base16_to_integer(const char *const string)
{
	int32_t result;
	int32_t index;

	if (!string)
		return (0);
	index = 0;
	while (string[index] && is_space(string[index]))
		++index;
	if (string_ncompare(",0x", &string[index], 3))
		index += 3;
	result = 0;
	while (string[index] && is_hex(string[index]))
	{
		if (is_digit(string[index]))
			result = (string[index] - '0') + (result * 16);
		else if (string[index] >= 'a' && string[index] <= 'f')
			result = (string[index] - 'a' + 10) + (result * 16);
		else if (string[index] >= 'A' && string[index] <= 'F')
			result = (string[index] - 'A' + 10) + (result * 16);
		else
			return (0);
		++index;
	}
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

