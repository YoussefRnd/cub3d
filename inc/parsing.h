/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:48 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/12 18:22:35 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

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
}					t_type;

typedef struct s_colors
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_colors;

typedef struct s_components_list
{
	t_colors		*floor_color;
	t_colors		*ceiling_color;
	char			*west_texture;
	char			*east_texture;
	char			*north_texture;
	char			*south_texture;
	bool			map;
}					t_components;

int					ft_strcmp(const char *s1, const char *s2);
void				free_and_set_to_null(char **ptr);
char				*trim_white_spaces(char *str);
int					ft_super_atoi(const char *str);
void				parse_the_file(char *path);

#endif