/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:06 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/10 11:54:46 by hbrahimi         ###   ########.fr       */
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

void parse_the_file(char *path)
{
    int fd;
    t_booleans those;

    fd = open_file_and_return_fd(path);
    if (!check_validity_of_file(fd))
        return ;
}




// bool check_validity_of_map(int fd)
// {
    
// }
