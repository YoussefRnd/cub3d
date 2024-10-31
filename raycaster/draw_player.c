/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:31:14 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/29 17:45:37 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	draw_line(t_game *game, t_line line)
{
	double	dx;
	double	dy;
	double	step;
	double	x;
	double	y;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	step = fmax(fabs(dx), fabs(dy));
	x = line.x0;
	y = line.y0;
	dx /= step;
	dy /= step;
	while (step-- >= 0)
	{
		mlx_put_pixel(game->win.img, round(x), round(y), line.color);
		x += dx;
		y += dy;
	}
}

// void	draw_player(t_game *game)
// {
// 	int		i;
// 	int		j;
// 	t_line	line;

// 	i = 0;
// 	while (i < PLAYER_SIZE)
// 	{
// 		j = 0;
// 		while (j < PLAYER_SIZE)
// 		{
// 			mlx_put_pixel(game->win.img, game->player.pos_in_pix.x - (MINIMAP_WIDTH / 2) - PLAYER_SIZE
// 				/ 2 + i, game->player.pos_in_pix.y - (MINIMAP_HEIGHT / 2) - PLAYER_SIZE / 2 + j,
// 				0x00FF00FF);
// 			j++;
// 		}
// 		i++;
// 	}
// 	line.x0 = game->player.pos_in_pix.x;
// 	line.y0 = game->player.pos_in_pix.y;
// 	line.x1 = line.x0 + (cos(game->player.angle) * (TILE_SIZE / 2));
// 	line.y1 = line.y0 + (sin(game->player.angle) * (TILE_SIZE / 2));
// 	line.color = 0xFF00FFFF;
// 	draw_line(game, line);
// 	mlx_image_to_window(game->win.mlx, game->win.img, 0, 0);
// }
