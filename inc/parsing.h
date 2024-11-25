/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:48 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/11/25 18:52:53 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../get_next_line/get_next_line.h"
# include "../lib/Libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
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

typedef struct s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct s_colors
{
	int				red;
	int				green;
	int				blue;
}					t_colors;

typedef struct s_mapp
{
	char			*line;
	struct s_mapp	*next;
}					t_mapp;

typedef struct s_components_list
{
	t_colors		*floor_color;
	t_colors		*ceiling_color;
	char			*path_to_west_texture;
	char			*path_to_east_texture;
	char			*path_to_north_texture;
	char			*path_to_south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	t_mapp			*map;
}					t_components;

int					ft_strcmp(const char *s1, const char *s2);
void				free_and_set_to_null(char **ptr);
char				*trim_white_spaces(char *str);
int					ft_super_atoi(const char *str);
bool				parse_the_file(char *path, t_components *comps);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				**list_to_array(t_mapp *head, int max_length);
int					get_max_string_length(t_mapp *head);
void				determine_player_pos(t_pos *pos, char **arr);
bool				is_a_position_char(char c);
int					get_color(t_colors *color);
void				free_comps(t_components *comps);

#endif