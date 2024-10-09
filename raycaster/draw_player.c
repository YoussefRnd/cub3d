/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:31:14 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/06 17:21:38 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_put_pixel(game->win.mini_map, game->player.pos.x * (TILE_SIZE
					+ 1) + (TILE_SIZE / 2) - (PLAYER_SIZE / 2) + j,
				game->player.pos.y * (TILE_SIZE + 1) + (TILE_SIZE / 2)
				- (PLAYER_SIZE / 2) + i, 0x00FF00FF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->win.mlx, game->win.mini_map, 0, 0);
}
