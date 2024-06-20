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

t_vec3 parser_parse_entry(char *const entry, const int32_t x, const int32_t y, int32_t *const out_color)
{
	char   *maybe_color;
	int32_t z;

	z = 0;
	maybe_color = NULL;
	z = string_to_base(entry, &maybe_color, 10);
	if (maybe_color && *maybe_color != '\0')
		*out_color = string_to_base(maybe_color, &maybe_color, 16);
	else
		*out_color = DEFAULT_COLOR;
	return (vec3(x, y, z));
}

bool parser_parse(t_parser *const self, const int32_t width, const int32_t height, char **rows)
{
	int32_t token_count;
	char  **entries;
	int32_t y;
	int32_t x;

	y = 0;
	while (y < height)
	{
		x = 0;
		entries = string_tokenize(rows[y], ' ');
		token_count = string_count(rows[y], " ");
		if (token_count != width)
			return (false);
		while (x < width)
		{
			self->map_coords[y][x] = parser_parse_entry(entries[x], x, y, &self->map_colors[y][x]);
			++x;
		}
		split_destroy(entries);
		++y;
	}
	parser_find_min_max(self, width, height);
	return (true);
}

void parser_find_min_max(t_parser *const self, const int32_t width, const int32_t height)
{
	int32_t y;
	int32_t x;
	t_vec3  v;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			v = self->map_coords[y][x];
			if (v.z < self->map_min.z)
				self->map_min = vec3(0, 0, v.z);
			if (v.z > self->map_max.z)
				self->map_max = vec3(width, height, v.z);
			++x;
		}
		++y;
	}
}
