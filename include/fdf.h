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

#define MOVE_STEP 20
#define ROTA_STEP 5
#define ZOOM_STEP 0.1f
#define SCAL_STEP 0.1f
#define COS30 0.86602540378f
#define SIN30 0.5f

/* RENDERER */

void draw(t_fdf_container *const self, const int32_t width, const int32_t height);
void draw_clear(t_fdf_container *const self, const int32_t width, const int32_t height);
void draw_line(t_fdf_container *const self, t_vec3 p0, t_vec3 p1);
void draw_pixel(t_fdf_container *const self, const t_vec3 pixel);

/* CONTAINER */
t_fdf_container *fdf_container_create(const char *const file_name);
bool             fdf_container_run(t_fdf_container *const self);
t_fdf_container *fdf_container_destroy(t_fdf_container *const self);

/*                                REFACTOR                                    */

/* FILE */
t_file *file_create(const char *const file_name);
char   *file_open_read_to_end_alloc(t_file *const self);
int32_t file_open(t_file *const self);
int32_t file_size(t_file *const self);
t_file *file_destroy(t_file *const self);

/* PARSER */
t_parser *parser_create(const char *const file_name);
bool    parser_parse(t_parser *const self, const char *const file_buffer);
int32_t parser_get_map_width(t_parser *const self);
int32_t parser_get_map_height(t_parser *const self);
bool    parser_is_valid_map(t_parser *const self);
t_parser *parser_destroy(t_parser *const self);
uintptr_t   make_entry(const int32_t zaxis, const int32_t color);
int32_t     entry_get_color(const uintptr_t entry);
int32_t     entry_get_zaxis(const uintptr_t entry);

/* CAMERA */
t_camera *camera_create(const t_vec3 pos, const t_vec3 rot, const float_t zoom, const float_t z_scale);
void      camera_move(t_camera *const self, t_vec3 offset);
void      camera_rota(t_camera *const self, t_vec3 offset);
void      camera_zoom(t_camera *const self, float_t offset);
void      camera_scale(t_camera *const self, float_t offset);
t_camera *camera_destroy(t_camera *const self);

/* INPUTS */
int32_t inputs_on_program_exit(void *const handle);
int32_t inputs_on_key_press(const int32_t keycode, void *const handle);

/* MAP */
t_map *map_create(t_vector *const entries, const t_vec2 map_dim, const t_vec2 screen_dim);
t_vec3  *map_clone_world_coords_buffer(t_map *const self);
int32_t *map_clone_world_colors_buffer(t_map *const self);
t_map   *map_destroy(t_map *const self);

/* RENDERER2 */
t_renderer *renderer_create(t_map *const map, t_camera *const camera, const int32_t width, const int32_t height);
bool renderer_init(t_renderer *const self, t_map *const map, const int32_t width, const int32_t height);
bool renderer_deinit(t_renderer *const self, const int32_t height, const int32_t width);
t_renderer *renderer_destroy(t_renderer *const self);

void renderer_start(t_renderer *const self, const int32_t world_width, const int32_t world_height);
void renderer_world_translate(t_renderer *const self, const int32_t width, const int32_t height);
void renderer_world_rotate(t_renderer *const self, const int32_t width, const int32_t height);
void renderer_world_project(t_renderer *const self, const int32_t width, const int32_t height);
void renderer_world_center(t_renderer *const self, const int32_t width, const int32_t height);
void renderer_world_fill(t_renderer *const self, const int32_t width, const int32_t height);

/* UTILS */
int32_t base16_to_integer(const char *const string);
int32_t base10_to_integer(const char *const string);

void print_rendered(t_fdf_container *const self);
#endif
