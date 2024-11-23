/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:14:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/23 21:15:12 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	draw_walls(t_game *game, int i)
{
	double	distance_proj_plane;
	double	start;
	double	end;

	game->wall.distance = game->ray.distance * cos(game->ray.angle
			- game->player.angle);
	distance_proj_plane = (WIDTH / 2) / tan(FOV / 2);
	game->wall.height = (TILE_SIZE / game->wall.distance) * distance_proj_plane;
	start = (HEIGHT / 2) - (game->wall.height / 2);
	end = (HEIGHT / 2) + (game->wall.height / 2);
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (start < end)
	{
		mlx_put_pixel(game->win.img, i, start, game->ray.color);
		start++;
	}
}
