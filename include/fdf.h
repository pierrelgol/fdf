/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 05:27:25 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/14 05:27:25 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "common.h"

#define MOVE_STEP 10
#define ROTA_STEP 1
#define ZOOM_STEP 1
#define SCAL_STEP 1

/* FILE */
t_file *file_create(const char *const file_name);
char   *file_open_read_to_end_alloc(t_file *const self);
int32_t file_open(t_file *const self);
int32_t file_size(t_file *const self);
t_file *file_destroy(t_file *const self);

/* PARSER */
t_parser *parser_create(const char *const file_name);
bool parser_parse(t_parser *const self, const int32_t width, const int32_t height, char **rows);
t_parser *parser_destroy(t_parser *const self);

/* CAMERA */
t_camera *camera_create(const t_vec3 pos, const t_vec3 rot, const float_t zoom, const float_t z_scale);
void      camera_move(t_camera *const self, t_vec3 offset);
void      camera_rota(t_camera *const self, t_vec3 offset);
void      camera_zoom(t_camera *const self, float_t offset);
void      camera_scale(t_camera *const self, float_t offset);
t_camera *camera_destroy(t_camera *const self);

/* CONTAINER */

int32_t inputs_on_program_exit(void *const handle);
int32_t inputs_on_key_press(const int32_t keycode, void *const handle);

/* RENDERER */
t_renderer *renderer_create(t_fdf_container *const fdf, const t_parser *const config, const int32_t screen_width, const int32_t screen_height);
void renderer_init(t_renderer *const self, const int32_t width, const int32_t height);
void renderer_rendering_start(t_renderer *const self, const int32_t width, const int32_t height);
void initialize_renderer_values(t_renderer *self);
void renderer_fill_relative(t_renderer *const self, const int32_t x, const int32_t y);
void renderer_center_world_to_screen(t_renderer *const self, const int32_t world_width, const int32_t world_height);
void rotate(double *a, double *b, double cos_angle, double sin_angle);
void project_to_screen(t_renderer *self, double cos30, double sin30);
void renderer_offset_world_pos(t_renderer *const self, const int32_t world_width, const int32_t world_height);
void renderer_render(t_renderer *const self, const int32_t world_width, const int32_t world_height);
t_renderer *renderer_destroy(t_renderer *const self);

void draw(t_renderer *const self, const int32_t width, const int32_t height);
void draw_clear(t_renderer *const self, const int32_t width, const int32_t height);
void draw_line(t_renderer *const self, t_vec2 p0, t_vec2 p1, const t_vec2 colors);
void draw_pixel(t_renderer *const self, const t_vec2 pos, const int32_t color);

/* CONTAINER */
t_fdf_container *fdf_container_create(const char *const file_name);
bool             fdf_container_init(t_fdf_container *const self);
bool             fdf_container_run(t_fdf_container *const self);
t_fdf_container *fdf_container_destroy(t_fdf_container *const self);

/* UTILS */
int64_t string_to_base(const char *str, char **endptr, const int32_t base);
t_color color_lerp(float_t total_distance, float_t point_distance, t_color color_start, t_color color_end);

void screen_print(t_vec2 **coord, int32_t width, int32_t height);
void world_print(t_vec3 **coord, int32_t width, int32_t height);
#endif
