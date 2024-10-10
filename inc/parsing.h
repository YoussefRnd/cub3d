/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:48 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/10 16:01:26 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>

typedef enum e_types
{
	FLOOR,
	CEILING,
	WEST,
	EAST,
	NORTH,
	SOUTH,
	MAP,
	INVALID
}			t_type;

typedef struct s_components_list
{
	char	*floor_color;
	char	*ceiling_color;
	char	*west_texture;
	char	*east_texture;
	char	*north_texture;
	char	*south_texture;
	bool	map;
}			t_components;

int			ft_strcmp(const char *s1, const char *s2);
void		free_and_set_to_null(void **ptr);

#endif