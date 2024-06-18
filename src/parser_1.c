/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:54:33 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 08:54:34 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	self->parsed_height = parser_parse_height(self, self->rows);
	if (!self->parsed_height)
		return (parser_destroy(self));
	self->parsed_width = parser_parse_width(self, self->rows);
	if (!self->parsed_width)
		return (parser_destroy(self));
	if (!parser_create_result_buffer(self, self->parsed_width,
			self->parsed_height))
		return (parser_destroy(self));
	return (self);
}

int32_t	parser_parse_width(t_parser *const self, char **rows)
{
	if (!self)
		return (0);
	return (string_count(rows[0], " "));
}

int32_t	parser_parse_height(t_parser *const self, char **rows)
{
	if (!self)
		return (0);
	return (split_size(rows));
}

void	parser_print(const t_parser *const self)
{
	print("--------------------------------\n");
	print("parser result :\n");
	print("parser->parsed_height = %d\n", self->parsed_height);
	print("parser->parsed_width  = %d\n", self->parsed_width);
	print("--------------------------------\n");
}

t_parser	*parser_destroy(t_parser *const self)
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
