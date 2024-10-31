/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:06 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/31 04:55:21 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	// printf("------>[%s]<-------\n", str);
	if (ft_strlen(str) == 0)
		return (false);
	while (*str)
	{
		if (*str != '0' && *str != '1' && *str != 'N' && *str != 'S'
			&& *str != 'E' && *str != 'W' && *str != ' ')
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
	if (!str)
		return (return_nd_free(INVALID, arr));
	if (!arr[0])
		return (return_nd_free(INVALID, arr));
	else if (valid_map_line(str))
		return (return_nd_free(MAP, arr));
	else if ((!(ft_strcmp(arr[0], "NO"))) && arr[1])
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
	else
		return (return_nd_free(INVALID, arr));
}

void	parse_texture_string(t_type info_type, char *temp, t_components *comps)
{
	char	**splitted;

	splitted = ft_split(temp, ' ');
	if (info_type == NORTH)
		comps->path_to_north_texture = ft_strdup(splitted[1]);
	else if (info_type == SOUTH)
		comps->path_to_south_texture = ft_strdup(splitted[1]);
	else if (info_type == EAST)
		comps->path_to_east_texture = ft_strdup(splitted[1]);
	else if (info_type == WEST)
		comps->path_to_west_texture = ft_strdup(splitted[1]);
	ft_free(splitted);
}

bool	parse_textures(t_type info_type, char *temp, t_components *comps)
{
	if (info_type == NORTH && comps->path_to_north_texture)
		return (false);
	else if (info_type == SOUTH && comps->path_to_south_texture)
		return (false);
	else if (info_type == EAST && comps->path_to_east_texture)
		return (false);
	else if (info_type == WEST && comps->path_to_west_texture)
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
	if (comps->ceiling_color && comps->path_to_east_texture && comps->floor_color
		&& comps->path_to_north_texture && comps->path_to_south_texture && comps->path_to_west_texture)
		return (true);
	else
		return (false);
}

char	*remove_newline(char *line)
{
	int		len;
	char	*temp;

	len = ft_strlen(line);
	if (len == 0)
		return (NULL);
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, line, len + 1);
	// printf("before:[%s]--->", temp);
	if (len > 0 && temp[len - 1] == '\n')
		temp[len - 1] = '\0';
	// printf("after:[%s]\n", temp);
	return (temp);
}

void	add_to_list(t_mapp **head, char *new_line)
{
	t_mapp	*new_node;
	t_mapp	*current;

	new_node = malloc(sizeof(t_mapp));
	if (!new_node)
		return ;
	new_node->line = ft_strdup(new_line);
	if (!new_node->line)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

bool	retrieve_map(int fd, t_components *comps, char *line)
{
	char	*cleaned_line;
	char	*temp;

	cleaned_line = remove_newline(line);
	add_to_list(&comps->map, cleaned_line);
	free_and_set_to_null(&cleaned_line);
	while ((line = get_next_line(fd)))
	{
		temp = remove_newline(line);
		free_and_set_to_null(&line);
		if (detect_type(temp) != MAP)
		{
			// printf("[%s], %d", temp, detect_type(temp));
			return (return_bool_nd_free(false, &temp));
		}
		add_to_list(&comps->map, temp);
		free_and_set_to_null(&temp);
	}
	return (true);
}

bool	fill_it(int fd, t_components *comps)
{
	char	*line;
	char	*temp;
	t_type	info_type;

	while ((line = get_next_line(fd)))
	{
		temp = trim_white_spaces(line);
		// free_and_set_to_null(&line);
		if (ft_strlen(temp) == 0)
		{
			free_and_set_to_null(&temp);
			continue ;
		}
		info_type = detect_type(temp);
		if (info_type == MAP)
		{
			if (!retrieve_map(fd, comps, line))
				return (free_and_set_to_null(&line), return_bool_nd_free(false,
						&temp));
			if (all_good(comps))
				return (free_and_set_to_null(&line), return_bool_nd_free(true,
						&temp));
			return (free_and_set_to_null(&line), return_bool_nd_free(false,
					&temp));
		}
		else if (info_type == INVALID)
			return (free_and_set_to_null(&line), return_bool_nd_free(false,
					&temp));
		if (!fill_container(info_type, temp, comps))
			return (free_and_set_to_null(&line), return_bool_nd_free(false,
					&temp));
		free_and_set_to_null(&line);
	}
	// ?to check later
	return (false);
}

void	set_all_to_null(t_components *comps)
{
	comps->ceiling_color = NULL;
	comps->floor_color = NULL;
	comps->path_to_east_texture = NULL;
	comps->path_to_west_texture = NULL;
	comps->path_to_north_texture = NULL;
	comps->path_to_south_texture = NULL;
	comps->west_texture = NULL;
	comps->south_texture = NULL;
	comps->north_texture = NULL;
	comps->east_texture = NULL;
	comps->map = NULL;
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
	printf("West texture: %s\n", components->path_to_west_texture);
	printf("East texture: %s\n", components->path_to_east_texture);
	printf("North texture: %s\n", components->path_to_north_texture);
	printf("South texture: %s\n", components->path_to_south_texture);
}
// TODO write an algorithm about how to parse that map

bool	adjacent_space(char *line)
{
	if (*line == ' ')
	{
		if (*(line - 1) != ' ' && *(line - 1) != '1')
			return (false);
		if (*(line + 1) != ' ' && *(line + 1) != '1' && *(line + 1) != '\0')
			return (false);
	}
	return (true);
}

bool	treat_middle_line(char *line)
{
	while (*line && *line == ' ')
		line++;
	if (*line != '1')
		return (false);
	while (*line)
	{
		if (!adjacent_space(line))
			return (false);
		line++;
	}
	line--;
	while (*line && *line == ' ')
		line--;
	if (*line != '1')
		return (false);
	return (true);
}

bool	treat_first_and_last(char *line)
{
	// printf("[%s]\n", line);
	while (*line && *line == ' ')
		line++;
	while (*line)
	{
		if (*line != ' ' && *line != '1')
			return (false);
		line++;
	}
	return (true);
}
bool	is_a_position_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}
bool	check_player_position(t_mapp *map)
{
	t_mapp	*current;
	int		position_char_count;
	int		i;

	i = -1;
	current = map;
	position_char_count = 0;
	while (current)
	{
		i = -1;
		while (current->line[++i])
		{
			if (is_a_position_char(current->line[i]))
				position_char_count++;
		}
		current = current->next;
	}
	if (position_char_count != 1)
		return (false);
	return (true);
}

char **list_to_array(t_mapp *head, int max_length)
{
    int count = 0;
    t_mapp *current = head;
    char **array;
    int i;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    array = (char **)malloc(sizeof(char *) * (count + 1));
    current = head;
    i = 0;
    while (current != NULL)
    {
        array[i] = (char *)malloc(max_length + 1);
        ft_strncpy(array[i], current->line, max_length);
        int len = strlen(current->line);
        if (len < max_length)
            ft_memset(array[i] + len, '\0', max_length - len);
        array[i][max_length] = '\0';
        current = current->next;
        i++;
    }
    array[i] = NULL;
    return array;
}

void	determine_player_pos(t_pos *pos, char **arr)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (is_a_position_char(arr[y][x]))
			{
				pos->y = y;
				pos->x = x;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	check_borders(char **map_arr, int x, int y, bool *out)
{
	if (!map_arr[y][x] || map_arr[y][x] == ' ')
	{
		*out = true;
		return ;
	}
	if (map_arr[y][x] == '1' || map_arr[y][x] == '2')
		return ;
	map_arr[y][x] = '2';
	// down
	if (map_arr[y + 1])
		check_borders(map_arr, x, y + 1, out);
	// right
	check_borders(map_arr, x + 1, y, out);
	// up
	check_borders(map_arr, x , y - 1, out);
	// left
	check_borders(map_arr, x - 1, y, out);
}

int	get_max_string_length(t_mapp *head)
{
	int	max_length;
	int	current_length;

	max_length = 0;
	while (head != NULL)
	{
		current_length = ft_strlen(head->line);
		if (current_length > max_length)
			max_length = current_length;
		head = head->next;
	}
	return (max_length);
}

bool	valid_map(t_mapp *map)
{
	// int		i = 0;
	int		max_length;
	bool	*out;
	char	**map_arr;
	t_pos	player_pos;

	// TODO free the double array and the bool when finished
	out = malloc(sizeof(bool *));
	*out = false;
	max_length = get_max_string_length(map);
	map_arr = list_to_array(map, max_length);
	determine_player_pos(&player_pos, map_arr);
	check_borders(map_arr, player_pos.x, player_pos.y, out);
	// while(map_arr[i])
	// {
	// 	printf("%s\n", map_arr[i]);
	// 	i++;
	// }
	if (*out)
		return (false);
	return (true);
}

bool	check_validity_of_map(t_mapp *map)
{
	t_mapp	*current;

	current = map->next;
	if (!treat_first_and_last(map->line))
		return (false);
	while (current->next)
	{
		if (!treat_middle_line(current->line))
			return (false);
		current = current->next;
	}
	if (!treat_first_and_last(current->line))
		return (false);
	if (!check_player_position(map) || !valid_map(map))
		return (false);
	return (true);
}
void	print_list(t_mapp *head)
{
	t_mapp	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->line);
		current = current->next;
	}
}

bool check_validity_of_textures(t_components *comps)
{
	// TODO free memory on failure

	comps->west_texture = mlx_load_png(comps->path_to_west_texture);
	comps->east_texture = mlx_load_png(comps->path_to_east_texture);
	comps->north_texture = mlx_load_png(comps->path_to_north_texture);
	comps->south_texture = mlx_load_png(comps->path_to_south_texture);
	if (!comps->west_texture | !comps->east_texture | !comps->north_texture | !comps->south_texture)
		return false;
	return true;
}

bool	parse_the_file(char *path, t_components *comps)
{
	int	fd;

	// TODO free comps on failure
	set_all_to_null(comps);
	fd = open_file_and_return_fd(path);
	if (!check_validity_of_file(fd))
		return false;
	if (!fill_it(fd, comps))
	{
		perror("Error");
		return false;
	}
	// if (!check_validity_of_textures(comps))
	// {
	// 	perror("Error");
	// 	return false;
	// }
	if (!check_validity_of_map(comps->map))
	{
		perror("Error");
		return false;
	}
	return true;
}
