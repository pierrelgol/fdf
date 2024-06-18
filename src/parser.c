/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:24:53 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 10:24:54 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_parser *parser_create(const char *const file_name)
{
	t_parser *self;

	self = memory_alloc(sizeof(t_parser));
	if (!self)
		return (NULL);
	self->file = file_create(file_name);
	if (!self->file)
		return (parser_destroy(self));
	self->rows = string_tokenize(self->file->buffer, '\n');
	if (!self->rows)
		return (parser_destroy(self));
	self->parsed_height = parser_parse_height(self, self->rows);
	if (!self->parsed_height)
		return (parser_destroy(self));
	self->parsed_width = parser_parse_width(self, self->rows);
	if (!self->parsed_width)
		return (parser_destroy(self));
	if (!parser_create_result_buffer(self, self->parsed_width, self->parsed_height))
		return (parser_destroy(self));
	return (self);
}

int32_t parser_parse_width(t_parser *const self, char **rows)
{
	if (!self)
		return (0);
	return (string_count(rows[0], " "));
}

int32_t parser_parse_height(t_parser *const self, char **rows)
{
	if (!self)
		return (0);
	return (split_size(rows));
}

bool parser_create_result_buffer(t_parser *const self, const int32_t width, const int32_t height)
{
	int32_t i;

	if (!self || width == 0 || height == 0)
		return (false);
	self->parsed_color_buffer = (int32_t *) memory_alloc(width * height * sizeof(int32_t));
	if (!self->parsed_color_buffer)
		return (false);
	self->parsed_zaxis_buffer = (int32_t *) memory_alloc(width * height * sizeof(int32_t *));
	if (!self->parsed_zaxis_buffer)
		return (false);
	self->color_matrix = (int32_t **) memory_alloc(height * sizeof(int32_t *));
	if (!self->color_matrix)
		return (false);
	self->zaxis_matrix = (int32_t **) memory_alloc(height * sizeof(int32_t *));
	if (!self->zaxis_matrix)
		return (false);
	i = 0;
	while (i < height)
	{
		self->color_matrix[i] = &self->parsed_color_buffer[i * width];
		self->zaxis_matrix[i] = &self->parsed_zaxis_buffer[i * width];
		++i;
	}
	return (true);
}

bool parser_parse_entry(const char *entry, int32_t *const out_z, int32_t *const out_color)
{
	char   *maybe_color;
	int32_t zaxis;
	int32_t color;

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

bool parser_parse(t_parser *const self, const int32_t width, const int32_t height, char **rows)
{
	char  **cols;
	int32_t i;
	int32_t j;

	i = 0;
	while (i < height)
	{
		j = 0;
		cols = string_tokenize(rows[i], ' ');
		while (j < width)
		{
			parser_parse_entry(cols[j], &self->parsed_zaxis_buffer[i * width + j], &self->parsed_color_buffer[i * width + j]);
			++j;
		}
		split_destroy(cols);
		++i;
	}
	return (true);
}

void parser_print(const t_parser *const self)
{
	print("--------------------------------\n");
	print("parser result :\n");
	print("parser->parsed_height = %d\n", self->parsed_height);
	print("parser->parsed_width  = %d\n", self->parsed_width);
	print("--------------------------------\n");
}

t_parser *parser_destroy(t_parser *const self)
{
	if (self)
	{
		if (self->parsed_color_buffer)
			memory_dealloc(self->parsed_color_buffer);
		if (self->parsed_zaxis_buffer)
			memory_dealloc(self->parsed_zaxis_buffer);
		if (self->color_matrix)
			memory_dealloc(self->color_matrix);
		if (self->zaxis_matrix)
			memory_dealloc(self->zaxis_matrix);
		if (self->rows)
			split_destroy(self->rows);
		if (self->file)
			file_destroy(self->file);
		memory_dealloc(self);
	}
	return (NULL);
}
