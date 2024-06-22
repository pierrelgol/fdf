/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:45:41 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 09:45:41 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	*map_clone_world_coords_buffer(t_map *const self)
{
	t_vec3	*result;

	if (!self)
		return (NULL);
	result = memory_dupe(self->world_coords_buffer, self->map_width
			* self->map_height * sizeof(t_vec3));
	if (!result)
		return (NULL);
	return (result);
}

int32_t	*map_clone_world_colors_buffer(t_map *const self)
{
	int32_t	*result;

	if (!self)
		return (NULL);
	result = memory_dupe(self->world_colors_buffer, self->map_width
			* self->map_height * sizeof(int32_t));
	if (!result)
		return (NULL);
	return (result);
}
