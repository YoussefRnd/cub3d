/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:21:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/29 18:17:08 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

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
			mlx_put_pixel(game->win.img, x * TILE_SIZE + j, y * TILE_SIZE + i,
				color);
			j++;
		}
		i++;
	}
}
void	draw_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = (MINIMAP_WIDTH / 2) - (PLAYER_SIZE / 2);
	player_y = (MINIMAP_HEIGHT / 2) - (PLAYER_SIZE / 2);
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_put_pixel(game->win.img, player_x + j, player_y + i,
				PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;
	int	map_x;
	int	map_y;
	int	line_start_x;
	int	line_start_y;
	int	line_end_x;
	int	line_end_y;

	start_x = game->player.pos_in_pix.x - (MINIMAP_WIDTH / 2);
	start_y = game->player.pos_in_pix.y - (MINIMAP_HEIGHT / 2);
	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			map_x = start_x + x;
			map_y = start_y + y;
			if (map_x >= 0 && map_y >= 0 && map_x < game->map.size.x * TILE_SIZE
				&& map_y < game->map.size.y * TILE_SIZE)
			{
				if (game->map.grid[map_y / TILE_SIZE][map_x / TILE_SIZE] == '1')
					mlx_put_pixel(game->win.img, x, y, WALL_COLOR);
				else
					mlx_put_pixel(game->win.img, x, y, FLOOR_COLOR);
			}
			else
				mlx_put_pixel(game->win.img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	draw_player(game);
	line_start_x = (MINIMAP_WIDTH / 2);
	line_start_y = (MINIMAP_HEIGHT / 2);
	line_end_x = line_start_x + (cos(game->player.angle) * (TILE_SIZE / 2));
	line_end_y = line_start_y + (sin(game->player.angle) * (TILE_SIZE / 2));
	draw_line(game, (t_line){line_start_x, line_start_y, line_end_x, line_end_y,
		0xFF00FFFF});
}
