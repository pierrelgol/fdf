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

bool	check_extension(const char *const file_name,
		const char *const extension)
{
	const uint64_t	file_name_len = string_length(file_name);
	const uint64_t	extension_len = string_length(extension);

	if (file_name_len <= extension_len)
		return (false);
	if (string_compare(&file_name[file_name_len - extension_len],
			extension) != 0)
		return (false);
	return (true);
}

int32_t	main(const int32_t ac, const char *const *const av)
{
	t_fdf_container	*fdf;

	if (ac == 2 && check_extension(av[1], ".fdf") == true)
	{
		fdf = fdf_container_create(av[1]);
		if (!fdf)
		{
			printf("Fatal error : fdf allocation failed\n");
			return (EXIT_FAILURE);
		}
		if (!fdf_container_run(fdf))
		{
			printf("Fatal error : fdf runtime failure\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
