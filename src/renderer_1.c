/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:42:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:42:43 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_renderer	*renderer_create(t_map *const map, const int32_t width, const int32_t height)
{	
	t_renderer	*self;

	self = memory_alloc(sizeof(t_renderer));
	if (!self)
		return (NULL);
	(void)map;
	(void)width;
	(void)height;
	// self->map = map;
	// self->width = width;
	// self->height = height;
	return  (self);
}
