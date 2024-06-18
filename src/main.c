/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 05:27:17 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/14 05:27:17 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

bool check_extension(const char *const file_name, const char *const extension)
{
	const uint64_t file_name_len = string_length(file_name);
	const uint64_t extension_len = string_length(extension);

	if (file_name_len <= extension_len)
		return (false);
	if (string_compare(&file_name[file_name_len - extension_len], extension) != 0)
		return (false);
	return (true);
}

int32_t main(const int32_t ac, const char *const *const av)
{
	t_fdf_container *self;

	if (ac == 2 && check_extension(av[1], ".fdf"))
	{
		self = fdf_container_create(av[1]);
		if (!self)
		{
			print("fdf_container : creation failure\n");
			return (EXIT_FAILURE);
		}
		if (!fdf_container_init(self))
		{
			print("fdf_container : initialization failure\n");
			self = fdf_container_destroy(self);
			return (EXIT_FAILURE);
		}
		if (fdf_container_run(self))
		{
			print("fdf_container : runtime failure\n");
			self = fdf_container_destroy(self);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
