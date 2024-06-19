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
	self->height = parser_parse_height(self, self->rows);
	if (!self->height)
		return (parser_destroy(self));
	self->width = parser_parse_width(self, self->rows);
	if (!self->width)
		return (parser_destroy(self));
	if (!parser_alloc(self, self->width, self->height))
		return (parser_destroy(self));
	return (self);
}

bool parser_alloc(t_parser *const self, const int32_t width, const int32_t height)
{
    int32_t i;

    if (!self || width == 0 || height == 0)
        return (false);

    self->map_colors_buffer = (int32_t *) memory_alloc(width * height * sizeof(int32_t));
    self->map_coords_buffer = (t_vec3 *) memory_alloc(width * height * sizeof(t_vec3));
    self->map_colors = (int32_t **) memory_alloc(height * sizeof(int32_t *));
    self->map_coords = (t_vec3 **) memory_alloc(height * sizeof(t_vec3 *));
    if (!self->map_coords_buffer || !self->map_coords || !self->map_colors_buffer || !self->map_colors)
        return (false);

    i = 0;
    while (i < height)
    {
        self->map_colors[i] = &self->map_colors_buffer[i * width];
        self->map_coords[i] = &self->map_coords_buffer[i * width];
        ++i;
    }
    return (true);
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

t_parser	*parser_destroy(t_parser *const self)
{
	if (self)
	{
		if (self->map_colors_buffer)
			memory_dealloc(self->map_colors_buffer);
		if (self->map_colors)
			memory_dealloc(self->map_colors);
		if (self->map_coords_buffer)
			memory_dealloc(self->map_coords_buffer);
		if (self->map_coords)
			memory_dealloc(self->map_coords);
		if (self->rows)
			split_destroy(self->rows);
		if (self->file)
			file_destroy(self->file);
		memory_dealloc(self);
	}
	return (NULL);
}
