/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:06 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/13 07:45:35 by hbrahimi         ###   ########.fr       */
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
	char	**arr;

	arr = ft_split(str, ' ');
	if ((!(ft_strcmp(arr[0], "NO"))) && arr[1])
		return (return_nd_free(NORTH, arr));
	else if ((!(ft_strcmp(arr[0], "SO"))) && arr[1])
		return (return_nd_free(SOUTH, arr));
	else if ((!(ft_strcmp(arr[0], "EA"))) && arr[1])
		return (return_nd_free(EAST, arr));
	else if ((!(ft_strcmp(arr[0], "WE"))) && arr[1])
		return (return_nd_free(WEST, arr));
	else if ((!(ft_strcmp(arr[0], "F"))) && arr[1])
		return (return_nd_free(FLOOR, arr));
	else if ((!(ft_strcmp(arr[0], "C"))) && arr[1])
		return (return_nd_free(CEILING, arr));
	else if (valid_map_line(str))
		return (return_nd_free(MAP, arr));
	else
		return (return_nd_free(INVALID, arr));
}

void	parse_texture_string(t_type info_type, char *temp, t_components *comps)
{
	char	**splitted;

	splitted = ft_split(temp, ' ');
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

int	where_to_start(t_type info_type, char *temp)
{
	int	i;

	i = 0;
	if (info_type == CEILING)
		i++;
	else if (info_type == FLOOR)
		i = i + 2;
	while (temp[i] && (temp[i] == 32 || temp[i] == 9))
		i++;
	return (i);
}

int	where_to_finish(int starting_index, char *temp)
{
	int	i;

	i = starting_index;
	while (temp[i] && temp[i] != '\0' && temp[i] != '\n')
		i++;
	i--;
	while (i >= starting_index && (temp[i] == ' ' || temp[i] == '\t'))
		i--;
	return (i + 1);
}

int	get_length(char *array[])
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		i++;
	}
	return (i);
}

bool	check_color_validity(char *str, int *color_value)
{
	*color_value = ft_super_atoi(str);
	if (*color_value < 0)
		return (false);
	else
		return (true);
}

bool	process_colors(char **array, t_colors *color)
{
	char	*trimmed;
	int		i;
	int		color_value;

	i = 0;
	while (i < 3)
	{
		trimmed = trim_white_spaces(array[i]);
		if (!check_color_validity(trimmed, &color_value))
		{
			free(trimmed);
			return (false);
		}
		if (i == 0)
			color->red = (unsigned char)color_value;
		else if (i == 1)
			color->green = (unsigned char)color_value;
		else if (i == 2)
			color->blue = (unsigned char)color_value;
		free(trimmed);
		i++;
	}
	return (true);
}

bool	deal_with_colors(t_type info_type, t_components *comps, char **splitted)
{
	if (info_type == CEILING)
	{
		comps->ceiling_color = malloc(sizeof(t_colors *));
		return (process_colors(splitted, comps->ceiling_color));
	}
	else if (info_type == FLOOR)
	{
		comps->floor_color = malloc(sizeof(t_colors *));
		return (process_colors(splitted, comps->floor_color));
	}
	return (false);
}

bool	parse_colors_string(t_type info_type, char *temp, t_components *comps)
{
	char	*colors_str;
	char	**splitted;
	int		starting_index;
	int		last_appearance;

	starting_index = where_to_start(info_type, temp);
	last_appearance = where_to_finish(starting_index, temp);
	colors_str = ft_substr(temp, starting_index, last_appearance
			- starting_index);
	splitted = ft_split(colors_str, ',');
	free_and_set_to_null(&colors_str);
	// !remember to free allocated memory before exiting
	if (get_length(splitted) != 3)
		return (false);
	if (!deal_with_colors(info_type, comps, splitted))
		return (false);
	return (true);
}

bool	parse_colors(t_type info_type, char *temp, t_components *comps)
{
	if (info_type == FLOOR && comps->floor_color)
		return (false);
	else if (info_type == CEILING && comps->ceiling_color)
		return (false);
	if (parse_colors_string(info_type, temp, comps))
		return (true);
	else
		return (false);
}

bool	fill_container(t_type info_type, char *temp, t_components *comps)
{
	if (info_type == NORTH || info_type == SOUTH || info_type == EAST
		|| info_type == WEST)
		return (parse_textures(info_type, temp, comps));
	else if (info_type == FLOOR || info_type == CEILING)
		return (parse_colors(info_type, temp, comps));
	return (false);
}

bool	return_bool_nd_free(bool boolean, char **temp)
{
	free(*temp);
	*temp = NULL;
	return (boolean);
}

bool	all_good(t_components *comps)
{
	if (comps->ceiling_color && comps->east_texture && comps->floor_color
		&& comps->north_texture && comps->south_texture && comps->west_texture)
		return (true);
	else
		return (false);
}

bool	fill_it(int fd, t_components *comps)
{
	char	*line;
	char	*temp;
	t_type	info_type;

	while ((line = get_next_line(fd)))
	{
		temp = trim_white_spaces(line);
		free_and_set_to_null(&line);
		if (ft_strlen(temp) == 0)
		{
			free_and_set_to_null(&temp);
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
	// ?to check later
	return (false);
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

void	print_components(const t_components *components)
{
	if (components == NULL)
	{
		printf("Components is NULL\n");
		return ;
	}
	printf("Floor color: %d, %d, %d\n", components->floor_color->red,
		components->floor_color->green, components->floor_color->blue);
	printf("Ceiling color: %d, %d, %d\n", components->ceiling_color->red,
		components->ceiling_color->green, components->ceiling_color->blue);
	printf("West texture: %s\n", components->west_texture);
	printf("East texture: %s\n", components->east_texture);
	printf("North texture: %s\n", components->north_texture);
	printf("South texture: %s\n", components->south_texture);
}

void	parse_the_file(char *path)
{
	int				fd;
	t_components	*comps;

	comps = malloc(sizeof(t_components));
	set_all_to_null(comps);
	fd = open_file_and_return_fd(path);
	if (!check_validity_of_file(fd))
		return ;
	if (!fill_it(fd, comps))
	{
		perror("Error");
		// return ;
	}
	print_components(comps);
}

// bool check_validity_of_map(int fd)
// {

// }
