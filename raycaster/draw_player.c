/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:31:14 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/26 19:20:45 by yboumlak         ###   ########.fr       */
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

void	draw_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = ((WIDTH / 5) / 2) - (PLAYER_SIZE / 2);
	player_y = (HEIGHT / 5 / 2) - (PLAYER_SIZE / 2);
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

void	draw_direction_line(t_game *game)
{
	int	line_start_x;
	int	line_start_y;
	int	line_end_x;
	int	line_end_y;

	line_start_x = ((WIDTH / 5) / 2);
	line_start_y = (HEIGHT / 5 / 2);
	line_end_x = line_start_x + (cos(game->player.angle) * (TILE_SIZE / 2));
	line_end_y = line_start_y + (sin(game->player.angle) * (TILE_SIZE / 2));
	draw_line(game, (t_line){line_start_x, line_start_y, line_end_x, line_end_y,
		0xFF00FFFF});
}
