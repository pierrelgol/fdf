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

	self = (t_fdf_container *) memory_alloc(sizeof(t_fdf_container));
	if (!self)
		return (NULL);
	self->parser = parser_create(file_name);
	if (!self->parser)
		return (fdf_container_destroy(self));
	if (!parser_parse(self->parser, self->parser->parsed_width, self->parser->parsed_height,
	                  self->parser->rows))
		return (fdf_container_destroy(self));
	self->renderer = renderer_create(self->parser, WIDTH, HEIGHT);
	if (!self->renderer)
		return (fdf_container_destroy(self));
	renderer_init(self->renderer);
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
	renderer_init(self->renderer);
	renderer_setup(self->renderer, self);
	draw(self->renderer);
	renderer_teardown(self->renderer, self);
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
		if (self->renderer)
			renderer_destroy(self->renderer);
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
	}
	return (NULL);
}
