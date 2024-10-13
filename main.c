/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:27:48 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/13 09:44:13 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/parsing.h"

// TODO check validity of textures
// TODO change the colors format to hexa

int main(int ac, char **av)
{
    t_components *comps;

    comps = malloc(sizeof(t_components));
    (void)ac;
    parse_the_file(av[1], comps);
    return 0;
}