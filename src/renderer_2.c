/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:44:47 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/18 13:44:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_renderer	*renderer_init(t_renderer *const self, const int32_t width, const int32_t height);
t_renderer	*renderer_deinit(t_renderer *const self);
t_renderer	*renderer_destroy(t_renderer *const self);
