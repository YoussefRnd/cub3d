/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:45:20 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/31 13:46:42 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	loop_hook(void *param);

void	init_events(t_game *game)
{
	mlx_set_cursor_mode(game->win.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(game->win.mlx, &loop_hook, game);
	mlx_close_hook(game->win.mlx, &mlx_close, game);
}

void	mlx_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_terminate(game->win.mlx);
	exit(EXIT_SUCCESS);
}

int	is_collision(t_game *game, t_pos next_pos)
{
	int top_left_x, top_left_y, top_right_x, top_right_y, bottom_left_x,
		bottom_left_y, bottom_right_x, bottom_right_y;
	top_left_x = (int)round(next_pos.x - PLAYER_SIZE / 2);
	top_left_y = (int)round(next_pos.y - PLAYER_SIZE / 2);
	top_right_x = (int)round(next_pos.x + PLAYER_SIZE / 2);
	top_right_y = (int)round(next_pos.y - PLAYER_SIZE / 2);
	bottom_left_x = (int)round(next_pos.x - PLAYER_SIZE / 2);
	bottom_left_y = (int)round(next_pos.y + PLAYER_SIZE / 2);
	bottom_right_x = (int)round(next_pos.x + PLAYER_SIZE / 2);
	bottom_right_y = (int)round(next_pos.y + PLAYER_SIZE / 2);
	if (game->map.grid[top_left_y / TILE_SIZE][top_left_x / TILE_SIZE] == '1'
		|| game->map.grid[top_right_y / TILE_SIZE][top_right_x
		/ TILE_SIZE] == '1' || game->map.grid[bottom_left_y
		/ TILE_SIZE][bottom_left_x / TILE_SIZE] == '1'
		|| game->map.grid[bottom_right_y / TILE_SIZE][bottom_right_x
		/ TILE_SIZE] == '1')
		return (1);
	return (0);
}

void	handle_keys(t_game *game)
{
	t_pos	next_pos_in_pix;

	next_pos_in_pix = game->player.pos_in_pix;
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_ESCAPE))
		mlx_close(game);
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_RIGHT))
		game->player.angle += 0.05;
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_LEFT))
		game->player.angle -= 0.05;
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_W))
	{
		next_pos_in_pix.x += PLAYER_SPEED * cos(game->player.angle);
		next_pos_in_pix.y += PLAYER_SPEED * sin(game->player.angle);
	}
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_S))
	{
		next_pos_in_pix.x -= PLAYER_SPEED * cos(game->player.angle);
		next_pos_in_pix.y -= PLAYER_SPEED * sin(game->player.angle);
	}
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_A))
	{
		next_pos_in_pix.x += PLAYER_SPEED * sin(game->player.angle);
		next_pos_in_pix.y -= PLAYER_SPEED * cos(game->player.angle);
	}
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_D))
	{
		next_pos_in_pix.x -= PLAYER_SPEED * sin(game->player.angle);
		next_pos_in_pix.y += PLAYER_SPEED * cos(game->player.angle);
	}
	if (!is_collision(game, next_pos_in_pix))
		game->player.pos_in_pix = next_pos_in_pix;
}

void	handle_cursor(t_game *game)
{
	int		center_x;
	int32_t	x;
	int32_t	y;

	center_x = WIDTH / 2;
	mlx_get_mouse_pos(game->win.mlx, &x, &y);
	if (x > 0)
		game->player.angle += (x - center_x) * 0.001;
	else
		game->player.angle -= (center_x - x) * 0.001;
	mlx_set_mouse_pos(game->win.mlx, center_x, HEIGHT / 2);
}

void	loop_hook(void *param)
{
	t_game *game;

	game = (t_game *)param;
	handle_keys(game);
	handle_cursor(game);
	cast_rays(game);
	draw_map(game);
}