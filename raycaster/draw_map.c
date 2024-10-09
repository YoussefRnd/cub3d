/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:21:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/08 17:33:04 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = 0;
	while (y < game->map.size.y)
	{
		x = 0;
		while (x < game->map.size.x)
		{
			i = 0;
			while (i < TILE_SIZE)
			{
				j = 0;
				while (j < TILE_SIZE)
				{
					if (game->map.grid[y][x] == '1')
						mlx_put_pixel(game->win.mini_map, x * (TILE_SIZE + 1)
							+ j, y * (TILE_SIZE + 1) + i, 0xFF0000FF);
					else if (game->map.grid[y][x] == '0'
						|| game->map.grid[y][x] == 'N'
						|| game->map.grid[y][x] == 'S'
						|| game->map.grid[y][x] == 'W'
						|| game->map.grid[y][x] == 'E')
					{
						mlx_put_pixel(game->win.mini_map, x * (TILE_SIZE + 1)
							+ j, y * (TILE_SIZE + 1) + i, 0xFFFFFFFF);
						game->player.pos_in_pix.x = x * (TILE_SIZE + 1) + j;
						game->player.pos_in_pix.y = y * (TILE_SIZE + 1) + i;
					}
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->win.mlx, game->win.mini_map, 0, 0);
}
