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
	int32_t  height;
	int32_t  width;

	t_vec3  *world_buffer;
	t_vec3 **world_coord;
	t_vec2	*screen_buffer;
	t_vec2 **screen_coord;
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
