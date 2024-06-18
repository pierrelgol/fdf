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
bool parser_create_result_buffer(t_parser *const self, const int32_t width, const int32_t height);
bool parser_parse_entry(const char *entry, int32_t *const out_z, int32_t *const out_color);
bool parser_parse(t_parser *const self, const int32_t width, const int32_t height, char **rows);
int32_t   parser_parse_width(t_parser *const self, char **rows);
int32_t   parser_parse_height(t_parser *const self, char **rows);
void      parser_print(const t_parser *const self);
t_parser *parser_destroy(t_parser *const self);

/* CONTAINER */

int32_t	inputs_on_program_exit(void *const handle);
int32_t	inputs_on_key_press(const int32_t keycode, void *const handle);


/* RENDERER */
t_renderer *renderer_create(const t_parser *const config, const int32_t screen_width, const int32_t screen_height);
void		renderer_init(t_renderer *const self, const int32_t width, const int32_t height);
bool		renderer_init_world(t_renderer *const self,const int32_t width, const int32_t height);
bool 		renderer_clear_world(t_renderer *const self);
bool		renderer_deinit_world(t_renderer *const self);
bool		renderer_init_screen(t_renderer *const self, const int32_t width, const int32_t height);
bool 		renderer_clear_screen(t_renderer *const self);
bool		renderer_deinit_screen(t_renderer *const self);
t_renderer *renderer_destroy(t_renderer *const self);


void renderer_clear(t_renderer *const self);
void renderer_setup(t_renderer *const self, const t_fdf_container *const fdf);
void draw(t_renderer *const self);
void draw_clear(t_renderer *const self);
void draw_line(t_renderer *const self, t_vec2 p0, t_vec2 p1, const t_vec2 colors);
void draw_pixel(t_renderer *const self, const t_vec2 pos, const int32_t color);
void renderer_from_world_to_projected(t_renderer *const self, const int32_t world_width, const int32_t world_height);

void rotate(double *a, double *b, double cos_angle, double sin_angle);
void initialize_renderer_values(t_renderer *self);
void project_to_screen(t_renderer *self, double cos30, double sin30);
void renderer_center_world_to_screen(t_renderer *const self, const int32_t world_width, const int32_t world_height);
void renderer_offset_world_pos(t_renderer *const self, const int32_t world_width, const int32_t world_height);



/* CONTAINER */
t_fdf_container	*fdf_container_create(const char *const file_name);
bool fdf_container_init(t_fdf_container *const self);
bool fdf_container_run(t_fdf_container *const self);
t_fdf_container	*fdf_container_destroy(t_fdf_container *const self);

/* UTILS */
int64_t string_to_base(const char *str, char **endptr, const int32_t base);

#endif
