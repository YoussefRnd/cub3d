/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:22:49 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/23 21:16:47 by yboumlak         ###   ########.fr       */
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
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!win->img)
		exit(EXIT_FAILURE);
}

void	init_ray(t_ray *ray)
{
	ray->is_facing_down = ray->angle > 0 && ray->angle < M_PI;
	ray->is_facing_up = !ray->is_facing_down;
	ray->is_facing_right = ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI;
	ray->is_facing_left = !ray->is_facing_right;
	ray->hor_inter = (t_pos){0, 0};
	ray->ver_inter = (t_pos){0, 0};
	ray->wall_hit = (t_pos){0, 0};
	ray->distance = 0;
	ray->color = 0;
	ray->was_hit_vertical = 0;
	ray->found_hor_wall_hit = false;
	ray->found_ver_wall_hit = false;
}
