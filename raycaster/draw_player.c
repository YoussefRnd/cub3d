/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:31:14 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/22 13:07:43 by yboumlak         ###   ########.fr       */
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
		mlx_put_pixel(game->win.img, line.x0, line.y0, line.color);
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
	int		scaled_player_size;
	float	scaled_x;
	float	scaled_y;

	scaled_player_size = PLAYER_SIZE * MINIMAP_SCALE;
	scaled_x = game->player.pos_in_pix.x * MINIMAP_SCALE;
	scaled_y = game->player.pos_in_pix.y * MINIMAP_SCALE;
	i = 0;
	while (i < scaled_player_size)
	{
		j = 0;
		while (j < scaled_player_size)
		{
			mlx_put_pixel(game->win.img, scaled_x - scaled_player_size / 2
				+ i, scaled_y - scaled_player_size / 2 + j, 0xFF00FFFF);
			j++;
		}
		i++;
	}
	line.x0 = scaled_x;
	line.y0 = scaled_y;
	line.x1 = scaled_x + cos(game->player.angle) * TILE_SIZE * MINIMAP_SCALE;
	line.y1 = scaled_y + sin(game->player.angle) * TILE_SIZE * MINIMAP_SCALE;
	line.color = 0xFF00FFFF;
	draw_line(game, line);
	mlx_image_to_window(game->win.mlx, game->win.img, 0, 0);
}
