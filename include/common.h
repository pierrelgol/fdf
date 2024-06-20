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
typedef struct s_camera        t_camera;
typedef struct s_fdf_container t_fdf_container;

typedef enum e_projection_type
{
	PROJECTION_ISO,
	PROJECTION_ORT,

} t_projection_type;
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
	char    **cols;
	int32_t   width;
	int32_t   height;
	int32_t  *zaxis_buffer;
	int32_t  *color_buffer;
	int32_t **zaxis_matrix;
	int32_t **color_matrix;
};

struct s_camera
{
	t_vec3            cam_position;
	double            deg_pitch;
	double            deg_yaw;
	double            deg_roll;
	double            rad_pitch;
	double            rad_yaw;
	double            rad_roll;
	double            cos_pitch;
	double            sin_pitch;
	double            cos_yaw;
	double            sin_yaw;
	double            cos_roll;
	double            sin_roll;
	float_t           z_scale;
	float_t           zoom;
	t_projection_type projection;
};

struct s_renderer
{
	t_parser *parser;
	void     *mlx_handle;
	void     *win_handle;
	void     *img_handle;
	char     *img_buffer;
	int32_t   img_size;
	int32_t   img_bpp;
	int32_t   img_endian;

	// NEW
	int32_t   height;
	int32_t   width;
	float_t   ratio_w;
	float_t   ratio_h;
	t_camera *camera;
	// OLD

	t_vec3   *world_coord_buffer;
	int32_t  *world_color_buffer;
	t_vec3  **world_coord;
	int32_t **world_color;

	t_vec2   *screen_coord_buffer;
	int32_t  *screen_color_buffer;
	t_vec2  **screen_coord;
	int32_t **screen_color;

	t_vec2 e;
	t_vec2 d;
	t_vec2 s;
	t_vec2 p;
	t_vec3 coord;
	double temp_x;
	double temp_y;
	double temp_z;
	double relative_x;
	double relative_y;
	double relative_z;
	double projected_x;
	double projected_y;
	double scale_factor;
	double screen_x;
	double screen_y;
	bool   is_dirty;
};

struct s_renderer_2
{
	int32_t height;
	int32_t width;
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
	t_camera   *camera;
};

#endif
