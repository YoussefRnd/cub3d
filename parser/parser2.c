/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:15:21 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/11/26 17:16:58 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

bool	check_validity_of_file(int fd)
{
	if (fd < 0)
	{
		perror("invalid file");
		return (false);
	}
	return (true);
}

bool	valid_map_line(char *str)
{
	if (ft_strlen(str) == 0)
		return (false);
	while (*str)
	{
		if (*str != '0' && *str != '1' && *str != 'N' && *str != 'S'
			&& *str != 'E' && *str != 'W' && *str != 32)
			return (false);
		str++;
	}
	return (true);
}

void	ft_free(char **splitted)
{
	int	c;

	c = 0;
	while (splitted[c])
	{
		free(splitted[c]);
		splitted[c] = NULL;
		c++;
	}
	free(splitted);
	return ;
}

t_type	return_nd_free(t_type this, char **arr)
{
	ft_free(arr);
	return (this);
}

int	get_color(t_colors *color)
{
	return (color->red << 24 | color->green << 16 | color->blue << 8 | 255);
}
