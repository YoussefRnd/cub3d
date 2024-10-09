/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:41:06 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/09 16:42:00 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int open_file_and_return_fd(char *path)
{
    int fd;

    if (!path)
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

    fd = open_file_and_return_fd(path);
    if (!check_validity_of_file(fd))
        return ;
}

bool check_validity_of_map(int fd)
{
        
}
