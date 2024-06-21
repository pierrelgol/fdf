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

void draw_clear(t_fdf_container *const self, const int32_t width, const int32_t height)
{
	int32_t x;
	int32_t y;

	y = 0;
	(void) height;
	(void) width;
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

void draw(t_fdf_container *const self, const int32_t width, const int32_t height)
{
	int32_t x;
	int32_t y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (y + 1 != height)
				draw_line(self, self->rendered[y][x], self->rendered[y + 1][x]);
			if (x + 1 != width)
				draw_line(self, self->rendered[y][x], self->rendered[y][x + 1]);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(self->mlx_handle, self->win_handle, self->img_handle, 0, 0);
	mlx_do_sync(self->mlx_handle);
}

static void draw_init_vars(t_bresenham_vars *const param, const t_vec3 *const a, const t_vec3 *const b)
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
}

int32_t dist(t_vec3 p, t_vec3 a, t_vec3 c)
{
	// Extract ARGB components from raw color values
	uint8_t a1 = (a.z >> 24) & 0xFF;
	uint8_t r1 = (a.z >> 16) & 0xFF;
	uint8_t g1 = (a.z >> 8) & 0xFF;
	uint8_t b1 = a.z & 0xFF;

	uint8_t a2 = (c.z >> 24) & 0xFF;
	uint8_t r2 = (c.z >> 16) & 0xFF;
	uint8_t g2 = (c.z >> 8) & 0xFF;
	uint8_t b2 = c.z & 0xFF;

	// Calculate distances
	float line_dx = c.x - a.x;
	float line_dy = c.y - a.y;
	float line_dist = sqrtf(line_dx * line_dx + line_dy * line_dy);

	float point_dx = p.x - a.x;
	float point_dy = p.y - a.y;
	float point_dist = sqrtf(point_dx * point_dx + point_dy * point_dy);
	float t = fminf(point_dist / line_dist, 1.0f);

	uint8_t ca = (uint8_t) ((float) a1 + (a2 - a1) * t);
	uint8_t cr = (uint8_t) ((float) r1 + (r2 - r1) * t);
	uint8_t cg = (uint8_t) ((float) g1 + (g2 - g1) * t);
	uint8_t cb = (uint8_t) ((float) b1 + (b2 - b1) * t);
	return (cb << 24) | (cg << 16) | (cr << 8) | ca;
}

void draw_line(t_fdf_container *const self, t_vec3 a, t_vec3 c)
{
	t_bresenham_vars param;
	t_vec3           p;

	draw_init_vars(&param, &a, &c);
	while (1)
	{
		p = vec3(param.x0, param.y0, DEFAULT_COLOR);
		p.z = dist(p, a, c);
		if (param.x0 >= 0 && param.x0 < WIDTH && param.y0 >= 0 && param.y0 < HEIGHT)
			draw_pixel(self, p);
		if (param.x0 == c.x && param.y0 == c.y)
			break;
		if (2 * param.err >= param.dy && param.x0 != c.x)
		{
			param.err += param.dy;
			param.x0 += param.sx;
		}
		if (2 * param.err <= param.dx && param.y0 != c.y)
		{
			param.err += param.dx;
			param.y0 += param.sy;
		}
	}
}

void draw_pixel(t_fdf_container *const self, const t_vec3 pos)
{
	if (pos.x >= 0 && pos.x < WIDTH && pos.y >= 0 && pos.y < HEIGHT)
	{
		char *pixel = self->img_buffer + (pos.y * self->img_size + pos.x * (self->img_bpp / 8));
		*(uint32_t *) pixel = (uint32_t) pos.z;
	}
}
