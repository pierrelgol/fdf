/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:09:50 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/19 12:09:50 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_vec_buffer(t_vec3 **buffer, int32_t width, int32_t height)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("{%6f,%6f,%6f}",buffer[y][x].x,buffer[y][x].y,buffer[y][x].z);
			++x;
		}
		printf("\n");
		fflush(stdout);
		++y;
	}
}

void	print_vec_buffer2(t_vec2 **buffer, int32_t width, int32_t height)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("{%6f,%6f}",buffer[y][x].x,buffer[y][x].y);
			++x;
		}
		printf("\n");
		fflush(stdout);
		++y;
	}
}
