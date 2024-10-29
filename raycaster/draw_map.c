/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:21:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/22 13:30:22 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	scaled_tile_size;

	scaled_tile_size = TILE_SIZE * MINIMAP_SCALE;
	i = 0;
	while (i < scaled_tile_size)
	{
		j = 0;
		while (j < scaled_tile_size)
		{
			mlx_put_pixel(game->win.img, x * scaled_tile_size + j, y
				* scaled_tile_size + i, color);
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

	game->win.img = mlx_new_image(game->win.mlx, WIDTH, HEIGHT);
	if (!game->win.img)
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
	mlx_image_to_window(game->win.mlx, game->win.img, 0, 0);
}
