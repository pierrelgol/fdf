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

// void draw_clear(t_renderer *const self)
// {
// 	int32_t x;
// 	int32_t y;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 			draw_pixel(self, vec2(x++, y), 0x00000000);
// 		++y;
// 	}
// }

// void draw(t_renderer *const self)
// {
// 	t_vec2  color;
// 	int32_t x;
// 	int32_t y;

// 	y = 1;
// 	draw_clear(self);
// 	while (y < self->world_height)
// 	{
// 		x = 1;
// 		while (x < self->world_width)
// 		{
// 			color = vec2(self->screen_color[y - 1][x],
					// self->screen_color[y][x]);
// 			draw_line(self, self->screen_coord[y - 1][x],
				// self->screen_coord[y][x], color);
// 			color = vec2(self->screen_color[y][x - 1],
					// self->screen_color[y][x]);
// 			draw_line(self, self->screen_coord[y][x - 1],
				// self->screen_coord[y][x], color);
// 			++x;
// 		}
// 		++y;
// 	}
// 	mlx_put_image_to_window(self->mlx_handle, self->win_handle,
		// self->img_handle, 0, 0);
// }

// void draw_line(t_renderer *const self, t_vec2 p0, t_vec2 p1, const t_vec2 c)
// {
// 	int32_t dx = abs(p1.x - p0.x);
// 	int32_t sx = p0.x < p1.x ? 1 : -1;
// 	int32_t dy = -abs(p1.y - p0.y);
// 	int32_t sy = p0.y < p1.y ? 1 : -1;
// 	int32_t err = dx + dy, e2; // error value e_xy
// 	t_vec2  p = vec2(p0.x, p0.y);

// 	while (1)
// 	{
// 		draw_pixel(self, p, color_lerp(p, p0, p1, color(c.u),
				// color(c.v)).color);
// 		if (p.x == p1.x && p.y == p1.y)
// 			break ;
// 		e2 = 2 * err;
// 		if (e2 >= dy)
// 		{
// 			err += dy;
// 			p.x += sx;
// 		}
// 		if (e2 <= dx)
// 		{
// 			err += dx;
// 			p.y += sy;
// 		}
// 	}
// }

// void draw_pixel(t_renderer *const self, const t_vec2 pos,
	// const int32_t color)
// {
// 	char *pixel;

// 	if (pos.x >= 0 && pos.x <= WIDTH && pos.y >= 0 && pos.y <= HEIGHT)
// 	{
// 		pixel = self->img_buffer + (pos.y * self->img_size + pos.x
				// * (self->img_bpp / 8));
// 		*(uint32_t *) pixel = (uint32_t) color;
// 	}
// }

// void renderer_from_world_to_projected(t_renderer *const self,
	// const int32_t world_width, const int32_t world_height,
	// const int32_t screen_width, const int32_t screen_height)
// {
//     const double cos30 = cos(30.0 * M_PI / 180.0);
//     const double sin30 = sin(30.0 * M_PI / 180.0);
//     const double map_center_x = screen_width / 2.0;
//     const double map_center_y = screen_height / 2.0;

//     double cos_pitch = cos(self->offset_pitch);
//     double sin_pitch = sin(self->offset_pitch);
//     double cos_yaw = cos(self->offset_yawn);
//     double sin_yaw = sin(self->offset_yawn);
//     double cos_roll = cos(self->offset_roll);
//     double sin_roll = sin(self->offset_roll);
//     double zoom = self->offset_zoom;

//     for (int y = 0; y < world_height; ++y)
//     {
//         for (int x = 0; x < world_width; ++x)
//         {
//             t_vec3 p = self->world_coord[y][x];

//             double relative_x = p.x + self->offset_x;
//             double relative_y = p.y + self->offset_y;
//             double relative_z = (p.z + self->offset_z) * self->z_amplitude;

//             double temp_x = relative_x * cos_yaw - relative_z * sin_yaw;
//             double temp_z = relative_x * sin_yaw + relative_z * cos_yaw;
//             relative_x = temp_x;
//             relative_z = temp_z;

//             double temp_y = relative_y * cos_pitch - relative_z * sin_pitch;
//             relative_z = relative_y * sin_pitch + relative_z * cos_pitch;
//             relative_y = temp_y;

//             temp_x = relative_x * cos_roll - relative_y * sin_roll;
//             relative_y = relative_x * sin_roll + relative_y * cos_roll;

//             relative_x = temp_x;

//             double projected_x = (relative_x - relative_y) * cos30;
//             double projected_y = (relative_x + relative_y) * sin30
	// - relative_z;

//             double scale_factor = 10.0 * zoom;
//             double screen_x = projected_x * scale_factor;
//             double screen_y = projected_y * scale_factor;

//             double normalized_x = screen_x / screen_width;
//             double normalized_y = screen_y / screen_height;

//             screen_x = normalized_x * screen_width;
//             screen_y = normalized_y * screen_height;

//             self->screen_coord[y][x] = vec2(screen_x, screen_y);
//             self->screen_color[y][x] = self->world_color[y][x];
//         }
//     }

//     for (int y = 0; y < world_height; ++y)
//     {
//         for (int x = 0; x < world_width; ++x)
//         {
//             self->screen_coord[y][x].x += map_center_x;
//             self->screen_coord[y][x].y += map_center_y;
//         }
//     }
// }

// void renderer_setup(t_renderer *const self, const t_fdf_container *const fdf)
// {
// 	self->mlx_handle = fdf->mlx_handle;
// 	self->win_handle = fdf->win_handle;
// 	self->img_handle = fdf->img_handle;
// 	self->img_buffer = fdf->img_buffer;
// 	self->img_endian = fdf->img_endian;
// 	self->img_size = fdf->img_size;
// 	self->img_bpp = fdf->img_bpp;
// }

// t_color color_lerp(t_vec2 p, t_vec2 start, t_vec2 end, t_color color_start,
	// t_color color_end)
// {
// 	float total_distance = vec2_distance(start, end);
// 	float point_distance = vec2_distance(start, p);

// 	float t = point_distance / total_distance;
// 	if (t < 0.0f)
// 		t = 0.0f;
// 	if (t > 1.0f)
// 		t = 1.0f;

// 	t_color result;
// 	result.a = (uint8_t) ((1 - t) * color_start.a + t * color_end.a);
// 	result.r = (uint8_t) ((1 - t) * color_start.r + t * color_end.r);
// 	result.g = (uint8_t) ((1 - t) * color_start.g + t * color_end.g);
// 	result.b = (uint8_t) ((1 - t) * color_start.b + t * color_end.b);

// 	return (result);
// }
