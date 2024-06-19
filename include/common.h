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
#define WIDTH 800
#define HEIGHT 600

#define MOVE_STEP 1.0f
#define ZOOM_STEP 1.0f
#define ZAMP_STEP 1.0f
#define ROTA_STEP 0.25f

typedef struct s_file          t_file;
typedef struct s_parser        t_parser;
typedef struct s_map           t_map;
typedef struct s_camera        t_camera;
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
	int32_t   width;
	int32_t   height;
	t_vec3    map_min;
	t_vec3    map_max;
	t_vec3   *map_coords_buffer;
	int32_t  *map_colors_buffer;
	t_vec3  **map_coords;
	int32_t **map_colors;
};

struct s_map
{
	t_parser *inputs;
	int32_t   height;
	int32_t   width;
	t_vec3    world_min;
	t_vec3    world_max;

	t_vec3   *world_coords_buffer;
	int32_t  *world_colors_buffer;
	t_vec3  **world_coords;
	int32_t **world_colors;
};

struct s_camera
{
	t_vec3  position;
	t_vec3  rotation;
	float_t zoom;
	float_t amplitude;
};

struct s_renderer
{
	void   *mlx_handle;
	void   *win_handle;
	void   *img_handle;
	char   *img_buffer;
	int32_t img_size;
	int32_t img_bpp;
	int32_t img_endian;

	int32_t   height;
	int32_t   width;
	t_map    *map_data;
	t_camera *camera;

	t_vec3   *world_coords_buffer;
	int32_t  *world_colors_buffer;
	t_vec3  **world_coords;
	int32_t **world_colors;

	t_vec2   *screen_coords_buffer;
	int32_t  *screen_colors_buffer;
	t_vec2  **screen_coords;
	int32_t **screen_colors;
};

struct s_fdf_container
{
	void     *mlx_handle;
	void     *win_handle;
	void     *img_handle;
	char     *img_buffer;
	int32_t   img_size;
	int32_t   img_bpp;
	int32_t   img_endian;
	t_camera *camera;
	t_parser *parser;
	t_map    *map;
	t_renderer *renderer;
};

#endif
