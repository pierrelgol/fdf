/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:01:10 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 08:01:11 by pollivie         ###   ########.fr       */
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
	self->entries = vector_create();
	if (!self->entries)
		return (parser_destroy(self));
	self->is_valid = true;
	if (!parser_parse(self, self->file->buffer))
		return (parser_destroy(self));
	self->map_dim = vec2(self->width, self->height);
	return (self);
}

t_parser	*parser_destroy(t_parser *const self)
{
	if (self)
	{
		if (self->entries)
			vector_destroy(self->entries);
		if (self->file)
			file_destroy(self->file);
		memory_dealloc(self);
	}
	return (NULL);
}

int32_t	parser_get_map_width(t_parser *const self)
{
	return (self->width);
}

int32_t	parser_get_map_height(t_parser *const self)
{
	return (self->height);
}

bool	parser_is_valid_map(t_parser *const self)
{
	return (self->is_valid);
}
