/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 08:19:46 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/14 08:19:47 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int32_t	char_to_digit(const char ch)
{
	if (ch >= '0' && ch <= '9')
		return (ch - '0');
	else if (ch >= 'A' && ch <= 'F')
		return (ch - 'A' + 10);
	else if (ch >= 'a' && ch <= 'f')
		return (ch - 'a' + 10);
	return (0);
}

int64_t	string_to_base(const char *str, char **endptr, const int32_t base)
{
	int64_t	result;
	bool	negative;

	negative = false;
	while (is_space(*str))
		++str;
	if (*str == '-' || *str == '+')
	{
		negative = true;
		++str;
	}
	if (base == 16)
		str += 3;
	result = 0;
	while (is_hex(*str))
		result = (char_to_digit(*str++)) + (result * base);
	if (*str == '\0')
		*endptr = NULL;
	else
		*endptr = (char *)str;
	return (((negative) * (-result)) + ((!negative) * (result)));
}
