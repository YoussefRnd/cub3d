/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:11:14 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/01/15 20:48:11 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clear(char **data)
{
	free(*data);
	*data = NULL;
}

void	read_from_file(int fd, char **raw_material)
{
	char	buffer[BUFFER_SIZE + 1];
	int		readed;

	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
		{
			free(*raw_material);
			*raw_material = NULL;
			return ;
		}
		buffer[readed] = '\0';
		*raw_material = concatenate(*raw_material, buffer);
		if (!*raw_material)
			return ;
		if ((*raw_material)[0] == '\0')
		{
			ft_clear(raw_material);
			return ;
		}
		if (find_nl(*raw_material))
			break ;
	}
}

char	*treat_container(char **the_rest)
{
	int		i;
	char	*deref;

	deref = *the_rest;
	i = 0;
	if (the_rest && *the_rest)
	{
		while (deref[i])
		{
			if (deref[i] == '\n')
				return (sub_str(deref, 0, i + 1));
			i++;
		}
		if (deref[i] == '\0')
			return (sub_str(deref, 0, i));
	}
	return (NULL);
}

char	*trash_blender(char *trash)
{
	int		i;
	char	*this;

	i = 0;
	while (trash[i] && trash[i] != '\n')
		i++;
	this = sub_str(trash, i + 1, ft_strlen(trash) - i);
	free(trash);
	trash = NULL;
	return (this);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*g_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(container);
		container = NULL;
	}
	read_from_file(fd, &container);
	g_line = treat_container(&container);
	if (!g_line)
	{
		free(container);
		container = NULL;
		return (NULL);
	}
	container = trash_blender(container);
	return (g_line);
}
