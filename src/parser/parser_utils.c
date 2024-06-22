/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:59:23 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 08:59:24 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uintptr_t	make_entry(const int32_t zaxis, const int32_t color)
{
	const uint32_t	zaxis_part = (uint32_t)zaxis;
	const uint32_t	color_part = (uint32_t)color;
	const uintptr_t	entry = ((uintptr_t)color_part << 32) | (uintptr_t)zaxis_part;

	return (entry);
}

int32_t	entry_get_color(const uintptr_t entry)
{
	return ((int32_t)(entry >> 32));
}

int32_t	entry_get_zaxis(const uintptr_t entry)
{
	return ((int32_t)(entry & 0xFFFFFFFF));
}
