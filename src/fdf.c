/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:27:46 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 12:27:46 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	fdf_container_init(t_fdf_container *const self)
{
	if (!self)
		return (false);
	self->mlx_handle = mlx_init();
	if (!self->mlx_handle)
		return (false);
	self->win_handle = mlx_new_window(self->mlx_handle, WIDTH, HEIGHT, "fdf");
	if (!self->win_handle)
		return (false);
	self->img_handle = mlx_new_image(self->mlx_handle, WIDTH, HEIGHT);
	if (!self->img_handle)
		return (false);
	self->img_buffer = mlx_get_data_addr(self->img_handle, &self->img_bpp,
			&self->img_size, &self->img_endian);
	if (!self->img_buffer)
		return (false);
	return (true);
}

t_fdf_container	*fdf_container_create(const char *const file_name)
{
	t_fdf_container	*fdf;
	t_parser		*parser;

	fdf = memory_alloc(sizeof(t_fdf_container));
	if (!fdf)
		return (NULL);
	fdf->parser = parser_create(file_name);
	if (!fdf->parser)
		return (fdf_container_destroy(fdf));
	parser = fdf->parser;
	fdf->map = map_create(parser->entries, vec2(parser->width, parser->height),
			vec2(WIDTH, HEIGHT));
	if (!fdf->map)
		return (fdf_container_destroy(fdf));
	fdf->camera = camera_create(vec3(0, 0, 0), vec3(0, 0, 0), 0.5f, 0.1f);
	if (!fdf->camera)
		return (fdf_container_destroy(fdf));
	fdf->renderer = renderer_create(fdf->map, fdf->camera, parser->width,
			parser->height);
	if (!fdf->renderer)
		return (fdf_container_destroy(fdf));
	if (!fdf_container_init(fdf))
		return (fdf_container_destroy(fdf));
	return (fdf);
}

bool	fdf_container_run(t_fdf_container *const self)
{
	if (!self)
		return (false);
	draw_clear(self, self->renderer->screen_width,
		self->renderer->screen_height);
	renderer_init(self->renderer, self->map, self->renderer->world_width,
		self->renderer->world_height);
	renderer_start(self->renderer, self->renderer->world_width,
		self->renderer->world_height);
	self->rendered = self->renderer->rendered;
	draw(self, self->renderer->world_width, self->renderer->world_height);
	renderer_deinit(self->renderer, self->renderer->world_width,
		self->renderer->world_height);
	mlx_hook(self->win_handle, 17, 9, inputs_on_program_exit, self);
	mlx_key_hook(self->win_handle, inputs_on_key_press, self);
	mlx_loop(self->mlx_handle);
	return (true);
}

t_fdf_container	*fdf_container_destroy(t_fdf_container *const self)
{
	if (self)
	{
		if (self->parser)
			parser_destroy(self->parser);
		if (self->camera)
			camera_destroy(self->camera);
		if (self->map)
			map_destroy(self->map);
		if (self->renderer)
			renderer_destroy(self->renderer);
		if (self->mlx_handle)
		{
			if (self->img_handle)
				mlx_destroy_image(self->mlx_handle, self->img_handle);
			if (self->win_handle)
				mlx_destroy_window(self->mlx_handle, self->win_handle);
			if (self->mlx_handle)
				mlx_destroy_display(self->mlx_handle);
			memory_dealloc(self->mlx_handle);
		}
		memory_dealloc(self);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
	return (NULL);
}
