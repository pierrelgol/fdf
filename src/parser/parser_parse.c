/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:58:38 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 08:58:38 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool parser2_parse_entry(t_parser *const self, const char *const entry)
{
	char  **result;
	int32_t zaxis;
	int32_t col;

	if (!self || !entry)
		return (false);
	result = string_tokenize(entry, ',');
	if (!result)
		return (false);
	zaxis = base10_to_integer(result[0]);
	if (result[1] != NULL)
		col = base16_to_integer(result[1]);
	else
		col = DEFAULT_COLOR;
	vector_insert_back(self->entries, make_entry(zaxis, col));
	split_destroy(result);
	return (true);
}

static bool parser2_parse_row(t_parser *const self, const char *const row)
{
	int32_t width;
	char  **cols;

	if (!self || !row)
		return (false);
	cols = string_tokenize(row, ' ');
	if (!cols)
		return (false);
	width = 0;
	while (cols[width])
	{
		parser2_parse_entry(self, cols[width]);
		++width;
	}
	self->prev_width = self->curr_width;
	self->curr_width = width;
	split_destroy(cols);
	return (true);
}

bool parser_parse(t_parser *const self, const char *const file_buffer)
{
	int32_t height;
	char  **rows;

	if (!self || !file_buffer)
		return (false);
	rows = string_tokenize(file_buffer, '\n');
	if (!rows)
		return (false);
	height = 0;
	while (rows[height] && self->is_valid)
	{
		parser2_parse_row(self, rows[height]);
		if (height != 0)
		{
			if (self->prev_width != self->curr_width)
				self->is_valid = false;
		}
		++height;
	}
	self->width = self->curr_width;
	self->height = height;
	split_destroy(rows);
	return (true);
}
