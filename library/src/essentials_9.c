/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:55:58 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/14 07:55:58 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/essentials.h"

uint64_t	split_length(char **split)
{
	uint64_t	length;
	uint64_t	i;

	if (!split || !*split)
		return (0);
	i = 0;
	length = 0;
	while (*(split + i))
	{
		length += string_length(split[i]);
		i += 1;
	}
	return (length);
}

char	**split_destroy(char **split)
{
	uint64_t	i;

	if (!split || !*split)
		return (NULL);
	i = 0;
	while (*(split + i))
	{
		memory_dealloc(*(split + i));
		i += 1;
	}
	memory_dealloc(split);
	return (NULL);
}

static uint64_t	string_count_words(const char *const source, const int32_t ch)
{
	uint64_t	count;
	uint64_t	i;

	count = 0;
	i = 0;
	if (!source)
		return (0);
	while (source[i])
	{
		while (source[i] && source[i] == ch)
			++i;
		if (source[i])
			++count;
		while (source[i] && source[i] != ch)
			++i;
	}
	return (count);
}

char	**string_tokenize(const char *const source, const int32_t ch)
{
	char		**result;
	uint64_t	size;
	uint64_t	start;
	uint64_t	end;
	uint64_t	i;

	if (!source)
		return (NULL);
	size = string_count_words(source, ch);
	result = split_create(size);
	if (!result)
		return (NULL);
	start = 0;
	i = 0;
	while (i < size && source[start])
	{
		start += string_span(&source[start], (char [2]){ch, 0x00});
		if (source[start] == '\0')
			break ;
		end = string_cspan(&source[start], (char [2]){ch, 0x00});
		result[i++] = string_nclone(&source[start], end);
		start += end;
	}
	result[i] = NULL;
	return (result);
}
