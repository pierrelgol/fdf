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

void	draw_clear(t_renderer *const self)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			draw_pixel(self, vec2(x, y), 0x00000000);
			++x;
		}
		++y;
	}
}

void	draw(t_renderer *const self)
{
	t_vec2	color;
	int32_t	x;
	int32_t	y;

	y = 1;
	draw_clear(self);
	while (y < self->world_height)
	{
		x = 1;
		while (x < self->world_width)
		{
			color = vec2(self->screen_color[y - 1][x],
					self->screen_color[y][x]);
			draw_line(self, self->screen_coord[y - 1][x],
				self->screen_coord[y][x], color);
			color = vec2(self->screen_color[y][x - 1],
					self->screen_color[y][x]);
			draw_line(self, self->screen_coord[y][x - 1],
				self->screen_coord[y][x], color);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(self->mlx_handle, self->win_handle,
		self->img_handle, 0, 0);
}

t_color	color_lerp(float_t total_distance, float_t point_distance,
		t_color color_start, t_color color_end)
{
	t_color	result;
	float	t;

	t = point_distance / total_distance;
	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
	result.a = (uint8_t)((1 - t) * color_start.a + t * color_end.a);
	result.r = (uint8_t)((1 - t) * color_start.r + t * color_end.r);
	result.g = (uint8_t)((1 - t) * color_start.g + t * color_end.g);
	result.b = (uint8_t)((1 - t) * color_start.b + t * color_end.b);
	return (result);
}

void	draw_line(t_renderer *const self, t_vec2 p0, t_vec2 p1, const t_vec2 c)
{
	const t_vec2	d = vec2(abs(p1.x - p0.x), -abs(p1.y - p0.y));
	const t_vec2	s = (t_vec2){
		.x = ((p0.x < p1.x) * 1) + ((p0.x >= p1.x) * -1),
		.y = ((p0.y < p1.y) * 1) + ((p0.y >= p1.y) * -1),
	};
	t_vec2			p;

	p = vec2(p0.x, p0.y);
	self->err1 = d.x + d.y;
	while (1)
	{
		draw_pixel(self, p, color_lerp(vec2_distance(p0, p1), vec2_distance(p,
					p0), color(c.u), color(c.v)).color);
		if (p.x == p1.x && p.y == p1.y)
			break ;
		self->err2 = 2 * self->err1;
		self->err1 += ((self->err2 >= d.y) * d.y) - ((self->err2 < d.y) * 0);
		p.x += ((self->err2 >= d.y) * s.x) - ((self->err2 < d.y) * 0);
		self->err1 += ((self->err2 <= d.x) * d.x) - ((self->err2 > d.x) * 0);
		p.y += ((self->err2 <= d.x) * s.y) - ((self->err2 > d.x) * 0);
	}
}

void	draw_pixel(t_renderer *const self, const t_vec2 pos,
		const int32_t color)
{
	char	*pixel;

	if (pos.x >= 0 && pos.x <= WIDTH && pos.y >= 0 && pos.y <= HEIGHT)
	{
		pixel = self->img_buffer + (pos.y * self->img_size + pos.x
				* (self->img_bpp / 8));
		*(uint32_t *)pixel = (uint32_t)color;
	}
}
