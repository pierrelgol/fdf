/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:36:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 16:36:14 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "assert.h"


void draw_clear(t_renderer *const self)
{
	int32_t x;
	int32_t y;

	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH - 1)
			draw_pixel(self, vec2(x++, y), 0x00000000);
		++y;
	}
}

void draw(t_renderer *const self, const int32_t height, const int32_t width)
{
	t_color2 color;
	int32_t x;
	int32_t y;

	y = 1;
	while (y < height)
	{
		x = 1;
		while (x < width)
		{
			color = color2(self->screen_colors[y - 1][x], self->screen_colors[y][x]);
			draw_line(self, self->screen_coords[y - 1][x], self->screen_coords[y][x], color);
			color = color2(self->screen_colors[y][x - 1], self->screen_colors[y][x]);
			draw_line(self, self->screen_coords[y][x - 1], self->screen_coords[y][x], color);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(self->mlx_handle, self->win_handle, self->img_handle, 0, 0);
}

void draw_pixel(t_renderer *const self, const t_vec2 pos, const int32_t color)
{
	char *pixel;
	const int32_t	x = (int32_t)pos.x;
	const int32_t	y = (int32_t)pos.y;

	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		pixel = self->img_buffer + (y * self->img_size + x * (self->img_bpp / 8));
		*(uint32_t *) pixel = (uint32_t) color;
	}
}

void draw_line(t_renderer *const self, t_vec2 p0, t_vec2 p1, t_color2 c2)
{
    // Calculate the differences
    float dx = p1.x - p0.x;
    float dy = p1.y - p0.y;

    // Calculate the number of steps needed
    int32_t steps = fmaxf(fabsf(dx), fabsf(dy));

    // Calculate the increment in x & y for each step
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    // Start at the initial point
    t_vec2 p = p0;

    // Loop through the steps
    for (int i = 0; i <= steps; ++i)
    {
        // Draw the pixel at the current position
        (void)c2;
        draw_pixel(self, vec2(roundf(p.x), roundf(p.y)), DEFAULT_COLOR);

        // Increment the x and y coordinates
        p.x += x_inc;
        p.y += y_inc;
    }
}

