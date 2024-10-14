/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:21:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/13 13:25:13 by yboumlak         ###   ########.fr       */
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
			mlx_put_pixel(game->win.mini_map, x * (TILE_SIZE + TILE_MARGIN) + j,
				y * (TILE_SIZE + TILE_MARGIN) + i, color);
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

	game->win.mini_map = mlx_new_image(game->win.mlx, WIDTH, HEIGHT);
	if (!game->win.mini_map)
		exit(EXIT_FAILURE);
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
	mlx_image_to_window(game->win.mlx, game->win.mini_map, 0, 0);
}
