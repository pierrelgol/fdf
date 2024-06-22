/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:14:31 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/21 13:14:32 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_rendered(t_fdf_container *const self)
{
	int32_t	i;
	int32_t	j;

	i = self->renderer->world_height / 2;
	j = self->renderer->world_width / 2;
	printf("{%d,%d,%d}", self->rendered[i][j].x, self->rendered[i][j].y,
		self->rendered[i][j].z);
	printf("\n");
}
