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
# define COMMON_H

# include "../library/include/essentials.h"
# include "../library/include/graphics.h"
# include "../library/include/vector.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 1
# endif

# define MOUSE_SCROLL_UP 1
# define MOUSE_SCROLL_DOWN 2
# define MOUSE_LEFT_BUTTON 3
# define MOUSE_RIGHT_BUTTON 4
# define FILE_RSIZE 1024
# define DEFAULT_COLOR 0x0000FF00
# define WIDTH 1280
# define HEIGHT 720

# define STEP 10.0f

typedef struct s_file			t_file;
typedef struct s_parser			t_parser;
typedef struct s_renderer		t_renderer;
typedef struct s_camera			t_camera;
typedef struct s_map			t_map;
typedef struct s_fdf_container	t_fdf_container;
typedef struct s_bresenham_vars	t_bresenham_vars;

struct							s_bresenham_vars
{
	int32_t						x0;
	int32_t						y0;
	int32_t						z0;
	int32_t						dx;
	int32_t						dy;
	int32_t						sx;
	int32_t						sy;
	int32_t						err;
	int32_t						err2;
};

typedef enum e_projection_type
{
	PROJECTION_ISO,
	PROJECTION_ORT,
}								t_projection_type;

struct							s_file
{
	char						*file_name;
	char						*buffer;
	int32_t						fd;
	int32_t						size;
};

struct							s_parser
{
	t_file						*file;
	bool						is_valid;
	int32_t						prev_width;
	int32_t						curr_width;
	int32_t						height;
	int32_t						width;
	t_vec2						map_dim;
	t_vector					*entries;
};

struct							s_map
{
	int32_t						map_width;
	int32_t						map_height;
	t_vec3						map_min;
	t_vec3						map_max;
	t_vec3						map_center;
	int32_t						screen_width;
	int32_t						screen_height;
	t_vec3						screen_center;
	t_vec3						*world_coords_buffer;
	t_vec3						**world_coords;
	int32_t						*world_colors_buffer;
	int32_t						**world_colors;
};

struct							s_renderer
{
	t_projection_type			projection;
	t_map						*map;

	t_camera					*camera;

	int32_t						world_height;
	int32_t						world_width;
	int32_t						screen_height;
	int32_t						screen_width;
	float_t						scale_factor;
	float_t						ratio_height;
	float_t						ratio_width;

	t_vec3						world_min;
	t_vec3						world_max;
	t_vec3						world_center;
	t_vec3						screen_center;

	t_vec3						*world_buffer;
	t_vec3						**world;
	int32_t						*colors_buffer;
	int32_t						**colors;

	t_vec3						world_absolute;
	t_vec3						world_relative;
	t_vec3						world_rotated;
	t_vec3						world_projected;
	t_vec3						screen;

	t_vec3						*rendered_buffer;
	t_vec3						**rendered;
};

struct							s_camera
{
	t_vec3						cam_position;
	double						deg_pitch;
	double						deg_yaw;
	double						deg_roll;
	double						rad_pitch;
	double						rad_yaw;
	double						rad_roll;
	double						cos_pitch;
	double						sin_pitch;
	double						cos_yaw;
	double						sin_yaw;
	double						cos_roll;
	double						sin_roll;
	float_t						z_scale;
	float_t						zoom;
	t_projection_type			projection;
};

struct							s_fdf_container
{
	void						*mlx_handle;
	void						*win_handle;
	void						*img_handle;
	char						*img_buffer;
	int32_t						img_size;
	int32_t						img_bpp;
	int32_t						img_endian;
	t_parser					*parser;
	t_map						*map;
	t_renderer					*renderer;
	t_camera					*camera;
	t_vec3						**rendered;
};

#endif
