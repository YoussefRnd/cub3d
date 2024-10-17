/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:31:14 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/17 17:22:39 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	draw_line(t_game *game, t_line line)
{
	t_bresenham_vars	bresenham;

	bresenham.dx = abs(line.x1 - line.x0);
	if (line.x0 < line.x1)
		bresenham.sx = 1;
	else
		bresenham.sx = -1;
	bresenham.dy = -abs(line.y1 - line.y0);
	if (line.y0 < line.y1)
		bresenham.sy = 1;
	else
		bresenham.sy = -1;
	bresenham.err = bresenham.dx + bresenham.dy;
	while (1)
	{
		mlx_put_pixel(game->win.mini_map, line.x0, line.y0, line.color);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		bresenham.e2 = 2 * bresenham.err;
		if (bresenham.e2 >= bresenham.dy)
		{
			bresenham.err += bresenham.dy;
			line.x0 += bresenham.sx;
		}
		if (bresenham.e2 <= bresenham.dx)
		{
			bresenham.err += bresenham.dx;
			line.y0 += bresenham.sy;
		}
	}
}

void	draw_player(t_game *game)
{
	int		i;
	int		j;
	t_line	line;

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_put_pixel(game->win.mini_map, game->player.pos_in_pix.x
				- PLAYER_SIZE / 2 + i, game->player.pos_in_pix.y - PLAYER_SIZE
				/ 2 + j, 0xFF00FFFF);
			j++;
		}
		i++;
	}
	line.x0 = game->player.pos_in_pix.x;
	line.y0 = game->player.pos_in_pix.y;
	line.x1 = game->player.pos_in_pix.x + cos(game->player.angle) * TILE_SIZE;
	line.y1 = game->player.pos_in_pix.y + sin(game->player.angle) * TILE_SIZE;
	line.color = 0xFF00FFFF;
	draw_line(game, line);
	mlx_image_to_window(game->win.mlx, game->win.mini_map, 0, 0);
}
