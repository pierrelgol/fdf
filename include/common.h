/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 05:22:59 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 05:23:00 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include "../library/include/essentials.h"
#include "../library/include/graphics.h"
#include "../library/include/vector.h"
#include "../mlx/mlx.h"
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef DEBUG
#define DEBUG 1
#endif

#define MOUSE_SCROLL_UP 1
#define MOUSE_SCROLL_DOWN 2
#define MOUSE_LEFT_BUTTON 3
#define MOUSE_RIGHT_BUTTON 4
#define FILE_RSIZE 1024
#define DEFAULT_COLOR 0x00FF0000
#define WIDTH 1280
#define HEIGHT 720

#define STEP 10.0f

typedef struct s_file          t_file;
typedef struct s_parser        t_parser;
typedef struct s_renderer      t_renderer;
typedef struct s_fdf_container t_fdf_container;

struct s_file
{
	char   *file_name;
	char   *buffer;
	int32_t fd;
	int32_t size;
};

struct s_parser
{
	t_file   *file;
	char    **rows;
	int32_t   parsed_width;
	int32_t   parsed_height;
	int32_t  *parsed_zaxis_buffer;
	int32_t  *parsed_color_buffer;
	int32_t **zaxis_matrix;
	int32_t **color_matrix;
};

struct s_renderer
{
	t_parser *parser;
	void   *mlx_handle;
	void   *win_handle;
	void   *img_handle;
	char   *img_buffer;
	int32_t img_size;
	int32_t img_bpp;
	int32_t img_endian;

	int32_t offset_x;
	int32_t offset_y;
	int32_t offset_z;
	float_t offset_zoom;
	float_t z_amplitude;
	float_t	offset_pitch;
	float_t	offset_yawn;
	float_t	offset_roll;

	t_vec3    cam_position;
	t_vec3    cam_target;
	t_vec3    cam_up;
	float     cam_fov;
	float     cam_aspect_ratio;
	float     cam_near_plane;
	float     cam_far_plane;

	float_t   ratio_w;
	float_t   ratio_h;
	int32_t   world_width;
	int32_t   world_height;
	t_vec3   *world_coord_buffer;
	int32_t  *world_color_buffer;
	t_vec3  **world_coord;
	int32_t **world_color;

	int32_t   screen_width;
	int32_t   screen_height;
	t_vec2   *screen_coord_buffer;
	int32_t  *screen_color_buffer;
	t_vec2  **screen_coord;
	int32_t **screen_color;

	float_t world_to_camera_matrix[4][4];
	float_t world_to_screen_matrix[4][4];
	float_t cam_view_matrix[4][4];
	float_t cam_projection_matrix[4][4];
	bool   is_dirty;
};

struct s_fdf_container
{
	void       *mlx_handle;
	void       *win_handle;
	void       *img_handle;
	char       *img_buffer;
	int32_t     img_size;
	int32_t     img_bpp;
	int32_t     img_endian;
	t_renderer *renderer;
	t_parser   *parser;
};

#endif
