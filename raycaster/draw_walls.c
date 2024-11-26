/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:14:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/26 19:33:55 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	draw_walls(t_game *game, int i)
{
	double	distance_proj_plane;
	double	start;
	double	end;
	double	wall_top;
	double	fov;

	fov = 60 * (M_PI / 180);
	game->wall.distance = game->ray.distance * cos(game->ray.angle
			- game->player.angle);
	distance_proj_plane = (WIDTH / 2) / tan(fov / 2);
	game->wall.height = (TILE_SIZE / game->wall.distance) * distance_proj_plane;
	start = (HEIGHT / 2) - (game->wall.height / 2);
	end = (HEIGHT / 2) + (game->wall.height / 2);
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	wall_top = start;
	while (start < end)
	{
		if (start >= 0)
			mlx_put_pixel(game->win.img, i, start, get_texture_color(game, start
					- wall_top));
		start++;
	}
}
