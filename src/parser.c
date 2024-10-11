/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:06 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/11 17:25:54 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

bool	valid_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (false);
	if (!(ft_strcmp(&path[len - 4], ".cub")))
		return (true);
	return (false);
}

int	open_file_and_return_fd(char *path)
{
	int	fd;

	if (!valid_path(path))
		return (-1);
	fd = open(path, O_RDONLY);
	return (fd);
}

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
	while (*str)
	{
		if (*str != '0' && *str != '1' && *str != 'N' && *str != 'S'
			&& *str != 'E' && *str != 'W')
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

t_type	detect_type(char *str)
{
	int	**arr;

	arr = ft_split(str, ' ');
	if (!(ft_strcmp(arr[0], "NO")))
		return (return_nd_free(NORTH, arr));
	else if (!(ft_strcmp(arr[0], "SO")))
		return (return_nd_free(SOUTH, arr));
	else if (!(ft_strcmp(arr[0], "EA")))
		return (return_nd_free(EAST, arr));
	else if (!(ft_strcmp(arr[0], "WE")))
		return (return_nd_free(WEST, arr));
	else if (!(ft_strcmp(arr[0], "F")))
		return (return_nd_free(FLOOR, arr));
	else if (!(ft_strcmp(arr[0], "C")))
		return (return_nd_free(CEILING, arr));
	else if (valid_map_line(str))
		return (return_nd_free(MAP, arr));
	else
		return (return_nd_free(INVALID, arr));
}

void parse_texture_string(t_type info_type, char *temp, t_components *comps)
{
    char **splitted;
    
    splitted = ft_split(temp, " ");
    if (info_type == NORTH)
        comps->north_texture = ft_strdup(splitted[1]);
    else if (info_type == SOUTH)
        comps->south_texture = ft_strdup(splitted[1]);    
    else if (info_type == EAST)
        comps->east_texture = ft_strdup(splitted[1]);  
    else if (info_type == WEST)
        comps->west_texture = ft_strdup(splitted[1]);
    ft_free(splitted);  
}

bool	parse_textures(t_type info_type, char *temp, t_components *comps)
{
	if (info_type == NORTH && comps->north_texture)
		return (false);
	else if (info_type == SOUTH && comps->south_texture)
		return (false);
	else if (info_type == EAST && comps->east_texture)
		return (false);
	else if (info_type == WEST && comps->west_texture)
		return (false);
	parse_texture_string(info_type, temp, comps);
	return (true);
}

// bool    parse_colors(info_type, temp, comps)
// {
          
// }

bool	fill_container(t_type info_type, char *temp, t_components *comps)
{
	if (info_type == NORTH || info_type == SOUTH || info_type == EAST
		|| info_type == WEST)
		return (parse_textures(info_type, temp, comps));
	else if (info_type == FLOOR || info_type == CEILING)
		return (parse_colors(info_type, temp, comps));
}

bool	return_bool_nd_free(bool boolean, char **temp)
{
	free(*temp);
	*temp = NULL;
	return boolean;
}

bool	all_good(t_components *comps)
{
	if (comps->ceiling_color && comps->east_texture && comps->floor_color
		&& comps->north_texture && comps->south_texture && comps->west_texture)
        return true;
    else
        return false;
}

bool	fill_it(int fd, t_components *comps)
{
	char	*line;
	char	*temp;
	t_type	info_type;

	// TODO free temp before exiting (make a func for it)
	// TODO empty line
	while (line = get_next_line(fd))
	{
		temp = ft_strtrim(line, " ");
		free_and_set_to_null(&line);
		if (ft_strlen(temp) == 0)
		{
			free(temp);
			temp = NULL;
			continue ;
		}
		info_type = detect_type(temp);
		if (info_type == MAP)
		{
			if (all_good(comps))
				return (return_bool_nd_free(true, &temp));
			return (return_bool_nd_free(false, &temp));
		}
		else if (info_type == INVALID)
			return (return_bool_nd_free(false, &temp));
		if (!fill_container(info_type, temp, comps))
			return (return_bool_nd_free(false, &temp));
	}
}

void	set_all_to_null(t_components *comps)
{
	comps->ceiling_color = NULL;
	comps->floor_color = NULL;
	comps->east_texture = NULL;
	comps->west_texture = NULL;
	comps->north_texture = NULL;
	comps->south_texture = NULL;
	comps->map = false;
}

void	parse_the_file(char *path)
{
	int				fd;
	t_components	*comps;

	comps = malloc(sizeof(t_components *));
	set_all_to_null(&comps);
	fd = open_file_and_return_fd(path);
	if (!check_validity_of_file(fd))
		return ;
	fill_it(fd, &comps);
}

// bool check_validity_of_map(int fd)
// {

// }
