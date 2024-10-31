/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:45:20 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/29 15:49:05 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	init_events(t_game *game)
{
	mlx_set_cursor_mode(game->win.mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(game->win.mlx, &key_hook, game);
	mlx_close_hook(game->win.mlx, &mlx_close, game);
	mlx_loop_hook(game->win.mlx, &cursor_hook, game);
}
void	cursor_hook(void *param)
{
	t_game	*game;
	int		center_x;
	int32_t x;
	int32_t y;
	

	game = (t_game *)param;
	center_x = WIDTH / 2;
	mlx_set_mouse_pos(game->win.mlx, center_x, HEIGHT / 2);
	mlx_get_mouse_pos(game->win.mlx, &x, &y);
	if (x > 0)
		game->player.angle += (x - center_x) * 0.001;
	else 
		game->player.angle -= (center_x - x) * 0.001;
	cast_rays(game);
	draw_map(game);
	draw_player(game);
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

void	key_hook(mlx_key_data_t kdata, void *param)
{
	t_game	*game;
	t_pos	next_pos_in_pix;

	game = (t_game *)param;
	next_pos_in_pix = game->player.pos_in_pix;
	if (kdata.key == MLX_KEY_ESCAPE && kdata.action == MLX_PRESS)
		mlx_close(game);
	else if (kdata.key == MLX_KEY_RIGHT && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
		game->player.angle += 0.1;
	else if (kdata.key == MLX_KEY_LEFT && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
		game->player.angle -= 0.1;
	else if (kdata.key == MLX_KEY_W && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
	{
		next_pos_in_pix.x += PLAYER_SPEED * cos(game->player.angle);
		next_pos_in_pix.y += PLAYER_SPEED * sin(game->player.angle);
	}
	else if (kdata.key == MLX_KEY_S && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
	{
		next_pos_in_pix.x -= PLAYER_SPEED * cos(game->player.angle);
		next_pos_in_pix.y -= PLAYER_SPEED * sin(game->player.angle);
	}
	else if (kdata.key == MLX_KEY_A && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
	{
		next_pos_in_pix.x += PLAYER_SPEED * sin(game->player.angle);
		next_pos_in_pix.y -= PLAYER_SPEED * cos(game->player.angle);
	}
	else if (kdata.key == MLX_KEY_D && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
	{
		next_pos_in_pix.x -= PLAYER_SPEED * sin(game->player.angle);
		next_pos_in_pix.y += PLAYER_SPEED * cos(game->player.angle);
	}
	if (!is_collision(game, next_pos_in_pix))
		game->player.pos_in_pix = next_pos_in_pix;
	cast_rays(game);
	draw_map(game);
	draw_player(game);
}
