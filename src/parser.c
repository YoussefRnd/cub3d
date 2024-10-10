/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:06 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/10 16:31:17 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

bool    valid_path(char *path)
{
    int len;

    len = ft_strlen(path);
    if (len < 4)
        return false;
    if (!(ft_strcmp(&path[len - 4], ".cub")))
        return true;
    return false;
}

int open_file_and_return_fd(char *path)
{
    int fd;

    if (!valid_path(path))
        return -1;
    fd = open(path, O_RDONLY);
    return fd;
}

bool check_validity_of_file(int fd)
{
    if (fd < 0)
    {
        perror("invalid file");
        return false;
    }
    return true;
}

t_type detect_type(char *str)
{
    // TODO free arr;
    int **arr;

    arr = ft_split(str, ' ');
    if (!(ft_strcmp(arr[0], "NO")))
        return NORTH;
    else if (!(ft_strcmp(arr[0], "SO")))
        return SOUTH;
    else if (!(ft_strcmp(arr[0], "EA")))
        return EAST;
    else if (!(ft_strcmp(arr[0], "WE")))
        return WEST;
    else if (!(ft_strcmp(arr[0], "F")))
        return FLOOR;
    else if (!(ft_strcmp(arr[0], "C")))
        return CEILING;
    // TODO valid_map_line
    else if (valid_map_line(str))
        return MAP;
}

bool fill_it(int fd, t_components *comps)
{
    // TODO free temp before exiting (make a func for it)
    char    *line;
    char    *temp;
    t_type  info_type;

    while (line = get_next_line(fd))
    {
        temp = ft_strtrim(line, " ");
        free_and_set_to_null(&line);
        info_type = detect_type(temp);
        if (info_type == MAP)
        {
            if (all_good(comps))
                return true;
            return false;
        }
        if (!fill_container(info_type ,temp, comps))
            return false;
    }
}

void    set_all_to_null(t_components *comps)
{
    comps->ceiling_color = NULL;
    comps->floor_color = NULL;
    comps->east_texture = NULL;
    comps->west_texture = NULL;
    comps->north_texture = NULL;
    comps->south_texture = NULL;
    comps->map = false;
}

void parse_the_file(char *path)
{
    int fd;
    t_components *comps;

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
