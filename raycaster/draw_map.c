/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:21:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/28 16:11:15 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(game->win.img, x * TILE_SIZE + j, y
				* TILE_SIZE + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < game->map.size.y)
	{
		x = 0;
		while (x < game->map.size.x)
		{
			if (game->map.grid[y][x] == '1')
				color = WALL_COLOR;
			else
				color = FLOOR_COLOR;
			draw_tile(game, x, y, color);
			x++;
		}
		y++;
	}
}
