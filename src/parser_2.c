/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <plgol.perso@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:54:38 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 08:54:39 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	parser_create_result_buffer(t_parser *const self, const int32_t width,
		const int32_t height)
{
	int32_t	i;

	if (!self || width == 0 || height == 0)
		return (false);
	self->parsed_color_buffer = (int32_t *)memory_alloc(width * height
			* sizeof(int32_t));
	self->parsed_zaxis_buffer = (int32_t *)memory_alloc(width * height
			* sizeof(int32_t *));
	if (!self->parsed_color_buffer || !self->parsed_zaxis_buffer)
		return (false);
	self->color_matrix = (int32_t **)memory_alloc(height * sizeof(int32_t *));
	self->zaxis_matrix = (int32_t **)memory_alloc(height * sizeof(int32_t *));
	if (!self->color_matrix || !self->zaxis_matrix)
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
			parser_parse_entry(cols[j], &self->parsed_zaxis_buffer[i * width
				+ j], &self->parsed_color_buffer[i * width + j]);
			++j;
		}
		split_destroy(cols);
		++i;
	}
	return (true);
}
