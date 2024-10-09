/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:22:49 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/05 12:24:18 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	init_window(t_win *win)
{
	win->title = "Cub3D";
	win->mlx = mlx_init(WIDTH, HEIGHT, win->title, false);
	if (!win->mlx)
		exit(EXIT_FAILURE);
	win->mini_map = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!win->mini_map)
		exit(EXIT_FAILURE);
}
