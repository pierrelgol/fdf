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

void draw_clear(t_renderer *const self, const int32_t height, const int32_t width)
{
	int32_t x;
	int32_t y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			draw_pixel(self, vec2(x, y), 0x00000000);
			++x;
		}
		++y;
	}
}

void draw(t_renderer *const self, const int32_t height, const int32_t width)
{
	t_vec2  color;
	int32_t x;
	int32_t y;

	y = 1;
	while (y < height)
	{
		x = 1;
		while (x < width)
		{
			color = vec2(self->screen_color[y - 1][x], self->screen_color[y][x]);
			draw_line(self, self->screen_coord[y - 1][x], self->screen_coord[y][x], color);
			color = vec2(self->screen_color[y][x - 1], self->screen_color[y][x]);
			draw_line(self, self->screen_coord[y][x - 1], self->screen_coord[y][x], color);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(self->mlx_handle, self->win_handle, self->img_handle, 0, 0);
}

void draw_line(t_renderer *const self, t_vec2 p0, t_vec2 p1, const t_vec2 c)
{
	(void)c;
	self->d = vec2(abs(p1.x - p0.x), -abs(p1.y - p0.y));
	self->s.x = ((p0.x < p1.x) * 1) + ((p0.x >= p1.x) * -1);
	self->s.y = ((p0.y < p1.y) * 1) + ((p0.y >= p1.y) * -1), self->p = vec2(p0.x, p0.y);
	self->e.x = self->d.x + self->d.y;
	while (1)
	{
		draw_pixel(self, self->p, DEFAULT_COLOR);
		// draw_pixel(self, self->p,
		//            color_lerp(vec2_distance(p0, p1), vec2_distance(self->p, p0), color(c.u), color(c.v))
		//                .color);
		if (self->p.x == p1.x && self->p.y == p1.y)
			break;
		self->e.y = 2 * self->e.x;
		self->e.x +=
		    ((self->e.y >= self->d.y) * self->d.y) - ((self->e.y < self->d.y) * 0);
		self->p.x +=
		    ((self->e.y >= self->d.y) * self->s.x) - ((self->e.y < self->d.y) * 0);
		self->e.x +=
		    ((self->e.y <= self->d.x) * self->d.x) - ((self->e.y > self->d.x) * 0);
		self->p.y +=
		    ((self->e.y <= self->d.x) * self->s.y) - ((self->e.y > self->d.x) * 0);
	}
	self->e = vec2(0, 0);
}

void draw_pixel(t_renderer *const self, const t_vec2 pos, const int32_t color)
{
	char *pixel;

	if (pos.x >= 0 && pos.x <= WIDTH && pos.y >= 0 && pos.y <= HEIGHT)
	{
		pixel = self->img_buffer + (pos.y * self->img_size + pos.x * (self->img_bpp / 8));
		*(uint32_t *) pixel = (uint32_t) color;
	}
}
