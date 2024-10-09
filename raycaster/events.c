/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:45:20 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/08 17:38:14 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	init_events(t_game *game)
{
	mlx_key_hook(game->win.mlx, &key_hook, game);
	mlx_close_hook(game->win.mlx, &mlx_close, game);
}

void	mlx_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_terminate(game->win.mlx);
	exit(EXIT_SUCCESS);
}

int is_collision(t_game *game, t_pos next_pos_in_pix)
{
	if (game->map.grid[(int)round(next_pos_in_pix.y / TILE_SIZE)][(int)round(next_pos_in_pix.x + (PLAYER_SIZE / 2) / TILE_SIZE)] == '1')
	{
		printf("collision\n");
		return (1);
	}
	return (0);
}

void	key_hook(mlx_key_data_t kdata, void *param)
{
	t_game	*game;
	t_pos	next_pos;

	game = (t_game *)param;
	next_pos = game->player.pos_in_pix;
	if (kdata.key == MLX_KEY_ESCAPE && kdata.action == MLX_PRESS)
		mlx_close(game);
	else if (kdata.key == MLX_KEY_UP && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
		next_pos.y -= 0.1;
	else if (kdata.key == MLX_KEY_DOWN && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
		next_pos.y += 0.1;
	else if (kdata.key == MLX_KEY_LEFT && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
		next_pos.x -= 0.1;
	else if (kdata.key == MLX_KEY_RIGHT && (kdata.action == MLX_PRESS
			|| kdata.action == MLX_REPEAT))
		next_pos.x += 0.1;
	if (!is_collision(game, next_pos))
		game->player.pos = next_pos;

	printf("x: %f, y: %f\n", game->player.pos.x, game->player.pos.y);
	printf("grid: %c\n", game->map.grid[(int)game->player.pos.y][(int)game->player.pos.x]);
	draw_map(game);
	draw_player(game);
}
