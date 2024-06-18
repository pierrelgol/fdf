/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:51:52 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 11:51:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf_container *fdf_container_create(const char *const file_name)
{
	t_fdf_container *self;
	t_parser        *parser;

	self = (t_fdf_container *) memory_alloc(sizeof(t_fdf_container));
	if (!self)
		return (NULL);
	self->parser = parser_create(file_name);
	if (!self->parser)
		return (fdf_container_destroy(self));
	parser = self->parser;
	if (!parser_parse(self->parser, parser->width, parser->height, parser->rows))
		return (fdf_container_destroy(self));
	self->camera = camera_create(vec3(parser->width / 2, parser->height / 2, 1), vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	if (!self->camera)
		return (fdf_container_destroy(self));
	return (self);
}

bool fdf_container_init(t_fdf_container *const self)
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
	self->img_buffer = mlx_get_data_addr(self->img_handle, &self->img_bpp, &self->img_size, &self->img_endian);
	if (!self->img_buffer)
		return (false);
	return (true);
}

bool fdf_container_run(t_fdf_container *const self)
{
	mlx_hook(self->win_handle, 17, 0, inputs_on_program_exit, self);
	mlx_key_hook(self->win_handle, inputs_on_key_press, self);
	mlx_loop(self->mlx_handle);
	return (true);
}

t_fdf_container *fdf_container_destroy(t_fdf_container *const self)
{
	if (self)
	{
		if (self->parser)
			parser_destroy(self->parser);
		if (self->camera)
			camera_destroy(self->camera);
		if (self->mlx_handle)
		{
			if (self->img_handle)
				mlx_destroy_image(self->mlx_handle, self->img_handle);
			if (self->win_handle)
				mlx_destroy_window(self->mlx_handle, self->win_handle);
			mlx_destroy_display(self->mlx_handle);
			memory_dealloc(self->mlx_handle);
		}
		memory_dealloc(self);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
	return (NULL);
}
