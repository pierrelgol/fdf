/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:43:40 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/20 10:43:40 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	parser_alloc(t_parser *const self, const int32_t width,
		const int32_t height)
{
	int32_t	i;

	if (!self || width == 0 || height == 0)
		return (false);
	self->color_buffer = (int32_t *)memory_alloc(width * height * sizeof(int32_t));
	self->zaxis_buffer = (int32_t *)memory_alloc(width * height * sizeof(int32_t *));
	if (!self->color_buffer || !self->zaxis_buffer)
		return (false);
	self->color_matrix = (int32_t **)memory_alloc(height * sizeof(int32_t *));
	self->zaxis_matrix = (int32_t **)memory_alloc(height * sizeof(int32_t *));
	if (!self->color_matrix || !self->zaxis_matrix)
		return (false);
	i = 0;
	while (i < height)
	{
		self->color_matrix[i] = &self->color_buffer[i * width];
		self->zaxis_matrix[i] = &self->zaxis_buffer[i * width];
		++i;
	}
	return (true);
}

bool	parser_parse_entry(const char *entry, int32_t *const out_z,
		int32_t *const out_color)
{
	char	*maybe_color;
	int32_t	zaxis;
	int32_t	color;

	if (!entry || !out_z || !out_color)
		return (false);
	zaxis = string_to_base(entry, &maybe_color, 10);
	if (maybe_color)
		color = string_to_base(maybe_color, &maybe_color, 16);
	else
		color = DEFAULT_COLOR;
	*out_z = zaxis;
	*out_color = color;
	return (true);
}

bool	parser_parse(t_parser *const self, const int32_t width,
		const int32_t height, char **rows)
{
	char	**cols;
	int32_t	i;
	int32_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		cols = string_tokenize(rows[i], ' ');
		while (j < width)
		{
			parser_parse_entry(cols[j], &self->zaxis_buffer[i * width
				+ j], &self->color_buffer[i * width + j]);
			++j;
		}
		split_destroy(cols);
		++i;
	}
	return (true);
}

t_parser	*parser_create(const char *const file_name)
{
	t_parser	*self;

	self = memory_alloc(sizeof(t_parser));
	if (!self)
		return (NULL);
	self->file = file_create(file_name);
	if (!self->file)
		return (parser_destroy(self));
	self->rows = string_tokenize(self->file->buffer, '\n');
	if (!self->rows)
		return (parser_destroy(self));
	self->cols = string_tokenize(self->rows[0], ' ');
	self->height= split_size(self->rows);
	self->width = split_size(self->cols);
	if (!parser_alloc(self, self->width, self->height))
		return (parser_destroy(self));
	printf("height = %d", self->height);
	printf("width = %d", self->width);
	fflush(stdout);
	return (self);
}

t_parser	*parser_destroy(t_parser *const self)
{
	if (self)
	{
		if (self->color_buffer)
			memory_dealloc(self->color_buffer);
		if (self->zaxis_buffer)
			memory_dealloc(self->zaxis_buffer);
		if (self->color_matrix)
			memory_dealloc(self->color_matrix);
		if (self->zaxis_matrix)
			memory_dealloc(self->zaxis_matrix);
		if (self->rows)
			split_destroy(self->rows);
		if (self->cols)
			split_destroy(self->cols);
		if (self->file)
			file_destroy(self->file);
		memory_dealloc(self);
	}
	return (NULL);
}

