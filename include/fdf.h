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

/* FILE */
t_file *file_create(const char *const file_name);
char   *file_open_read_to_end_alloc(t_file *const self);
int32_t file_open(t_file *const self);
int32_t file_size(t_file *const self);
t_file *file_destroy(t_file *const self);

/* PARSER */
t_parser *parser_create(const char *const file_name);
bool parser_alloc(t_parser *const self, const int32_t width, const int32_t height);
int32_t parser_parse_width(t_parser *const self, char **rows);
int32_t parser_parse_height(t_parser *const self, char **rows);
t_vec3 parser_parse_entry(char *const entry, const int32_t x, const int32_t y, int32_t *const out_color);
bool parser_parse(t_parser *const self, const int32_t width, const int32_t height, char **rows);
void parser_find_min_max(t_parser *const self, const int32_t width, const int32_t height);
t_parser *parser_destroy(t_parser *const self);

/* CONTAINER */
int32_t inputs_on_program_exit(void *const handle);
int32_t inputs_on_key_press(const int32_t keycode, void *const handle);

/* CAMERA */

t_camera *camera_create(const t_vec3 position, const t_vec3 rotation, const float_t zoom, const float_t amplitude);
void camera_update_position(t_camera *const self, const t_vec3 position_offset);
void camera_update_rotation(t_camera *const self, const t_vec3 rotation_offset);
void camera_update_zoom(t_camera *const self, const float_t zoom_offset);
void camera_update_amplitude(t_camera *const self, const float_t amplitude_offset);
t_vec3    camera_get_position(const t_camera *const self);
t_vec3    camera_get_rotation(const t_camera *const self);
t_vec3    camera_get_zoom(const t_camera *const self);
t_vec3    camera_get_amplitude(const t_camera *const self);
t_camera *camera_destroy(t_camera *const self);

void	camera_print(const t_camera *const self);

/* MAP */
t_map *map_create(t_parser *const config, const int32_t width, const int32_t height);
t_map *map_alloc(t_map *const self, t_parser *const config, const int32_t width, const int32_t height);
t_map *map_clone(t_map *const self);
t_map *map_destroy(t_map *const self);

/* RENDERER */

t_renderer *renderer_create(t_fdf_container *const fdf, t_camera *const camera, t_map *const map);
t_renderer *renderer_destroy(t_renderer *const self);

void	renderer_init_world_data(t_renderer *const self, const int32_t width, const int32_t height);

/* DRAW */
void draw_clear(t_renderer *const self);
void draw(t_renderer *const self);
void draw_line(t_renderer *const self, t_vec2 p0, t_vec2 p1, const t_vec2 c);
void draw_pixel(t_renderer *const self, const t_vec2 pos, const int32_t color);
// void draw_pixel_2(uint32_t *const img_buffer, const t_vec2 pos, const int32_t color);



/* CONTAINER */
t_fdf_container *fdf_container_create(const char *const file_name);
bool             fdf_container_init(t_fdf_container *const self);
bool             fdf_container_run(t_fdf_container *const self);
t_fdf_container *fdf_container_destroy(t_fdf_container *const self);

/* UTILS */
int64_t string_to_base(const char *str, char **endptr, const int32_t base);
void vec3_print(const char *label, const t_vec3 vec);

#endif
