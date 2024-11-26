/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:21:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/26 19:19:17 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

static void	draw_pixel(t_game *game, t_pos screen_pos, t_pos map_pos)
{
	if (map_pos.x >= 0 && map_pos.y >= 0 && map_pos.x < game->map.size.x
		* TILE_SIZE && map_pos.y < game->map.size.y * TILE_SIZE)
	{
		if (game->map.grid[(int)map_pos.y / TILE_SIZE][(int)map_pos.x
			/ TILE_SIZE] == '1')
			mlx_put_pixel(game->win.img, screen_pos.x, screen_pos.y,
				WALL_COLOR);
		else
			mlx_put_pixel(game->win.img, screen_pos.x, screen_pos.y,
				FLOOR_COLOR);
	}
	else
		mlx_put_pixel(game->win.img, screen_pos.x, screen_pos.y, 0x000000FF);
}

void	draw_minimap_grid(t_game *game, int start_x, int start_y)
{
	t_pos	screen_pos;
	t_pos	map_pos;

	screen_pos.y = 0;
	while (screen_pos.y < (HEIGHT / 5))
	{
		screen_pos.x = 0;
		while (screen_pos.x < (WIDTH / 5))
		{
			map_pos.x = start_x + screen_pos.x;
			map_pos.y = start_y + screen_pos.y;
			draw_pixel(game, screen_pos, map_pos);
			screen_pos.x++;
		}
		screen_pos.y++;
	}
}

void	draw_minimap(t_game *game)
{
	int	start_x;
	int	start_y;

	start_x = game->player.pos_in_pix.x - ((WIDTH / 5) / 2);
	start_y = game->player.pos_in_pix.y - ((HEIGHT / 5) / 2);
	draw_minimap_grid(game, start_x, start_y);
	draw_player(game);
	draw_direction_line(game);
}
