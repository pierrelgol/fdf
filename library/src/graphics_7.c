/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:11:52 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/15 08:11:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int32_t	clamp(const int32_t min, const int32_t value, const int32_t max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}
