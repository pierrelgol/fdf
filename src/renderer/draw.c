/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:48:34 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 09:48:35 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_clear(t_fdf_container *const self, const int32_t width,
		const int32_t height)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	(void)height;
	(void)width;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			draw_pixel(self, vec3(x, y, 0x00000000));
			++x;
		}
		++y;
	}
}

void	draw(t_fdf_container *const self, const int32_t width,
		const int32_t height)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if ((x + 1) < width)
				draw_line(self, self->rendered[y][x + 1], self->rendered[y][x]);
			if ((y + 1) < height)
				draw_line(self, self->rendered[y + 1][x], self->rendered[y][x]);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(self->mlx_handle, self->win_handle,
		self->img_handle, 0, 0);
	mlx_do_sync(self->mlx_handle);
}

static void	draw_init_vars(t_bresenham_vars *const param, const t_vec3 *const a,
		const t_vec3 *const b)
{
	param->dx = abs(b->x - a->x);
	param->dy = -1 * abs(b->y - a->y);
	if (a->x <= b->x)
		param->sx = 1;
	else
		param->sx = -1;
	if (a->y <= b->y)
		param->sy = 1;
	else
		param->sy = -1;
	param->err = param->dx + param->dy;
	param->x0 = a->x;
	param->y0 = a->y;
	param->z0 = a->z;
}

void	draw_line(t_fdf_container *const self, t_vec3 a, t_vec3 c)
{
	t_bresenham_vars	bres;

	draw_init_vars(&bres, &a, &c);
	while (1)
	{
		if (bres.x0 >= 0 && bres.x0 < WIDTH && bres.y0 >= 0 && bres.y0 < HEIGHT)
			draw_pixel(self, vec3(bres.x0, bres.y0, bres.z0));
		if (bres.x0 == c.x && bres.y0 == c.y)
			break ;
		if (2 * bres.err >= bres.dy && bres.x0 != c.x)
		{
			bres.err += bres.dy;
			bres.x0 += bres.sx;
		}
		if (2 * bres.err <= bres.dx && bres.y0 != c.y)
		{
			bres.err += bres.dx;
			bres.y0 += bres.sy;
		}
	}
}

void	draw_pixel(t_fdf_container *const self, const t_vec3 pos)
{
	char	*pixel;

	if (pos.x >= 0 && pos.x < WIDTH && pos.y >= 0 && pos.y < HEIGHT)
	{
		pixel = self->img_buffer + (pos.y * self->img_size + pos.x
				* (self->img_bpp / 8));
		*(uint32_t *)pixel = (uint32_t)color(pos.z).color;
	}
}
