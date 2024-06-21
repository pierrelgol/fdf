/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:56:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/14 06:56:07 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_file	*file_create(const char *const file_name)
{
	t_file	*self;

	self = (t_file *)memory_alloc(sizeof(t_file));
	if (!self)
		return (NULL);
	self->file_name = string_clone(file_name);
	if (!self->file_name)
		return (file_destroy(self));
	self->size = file_size(self);
	if (self->size <= 0)
		return (file_destroy(self));
	self->buffer = file_open_read_to_end_alloc(self);
	if (!self->buffer)
		return (file_destroy(self));
	return (self);
}

int32_t	file_open(t_file *const file)
{
	int32_t	fd;

	if (!file)
		return (-1);
	if (file->fd)
		return (file->fd);
	else
	{
		fd = open(file->file_name, O_RDONLY);
		return (fd);
	}
}

int32_t	file_size(t_file *const file)
{
	char	temp[FILE_RSIZE];
	int32_t	rbytes;
	int32_t	size;

	if (!file)
		return (0);
	if (file->fd == 0)
		file->fd = file_open(file);
	if (file->fd == -1)
		return (0);
	rbytes = (sizeof(temp) / sizeof(temp[0]));
	size = 0;
	while (rbytes == FILE_RSIZE)
	{
		rbytes = (int32_t)read(file->fd, temp, FILE_RSIZE);
		size += rbytes;
	}
	close(file->fd);
	file->fd = 0;
	return (size);
}

char	*file_open_read_to_end_alloc(t_file *const file)
{
	char	*buffer;
	int32_t	rsize;

	if (!file)
		return (NULL);
	file->fd = file_open(file);
	if (file->fd == -1)
		return (NULL);
	buffer = memory_alloc((uint64_t)file->size + 1);
	if (!buffer)
		return (NULL);
	rsize = read(file->fd, buffer, file->size);
	if (rsize == -1)
	{
		memory_dealloc(buffer);
		return (NULL);
	}
	buffer[rsize] = 0;
	return (buffer);
}

t_file	*file_destroy(t_file *const self)
{
	if (self)
	{
		if (self->file_name)
			memory_dealloc(self->file_name);
		if (self->fd != 0)
			self->fd = close(self->fd);
		if (self->buffer)
			memory_dealloc(self->buffer);
		memory_dealloc(self);
	}
	return (NULL);
}
