/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:45:20 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/25 18:11:00 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

void	mlx_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_terminate(game->win.mlx);
	exit(EXIT_SUCCESS);
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
	next_pos_in_pix = calculate_next_position(game, game->player.pos_in_pix);
	if (!is_collision(game, next_pos_in_pix))
		game->player.pos_in_pix = next_pos_in_pix;
}

void	handle_cursor(t_game *game)
{
	int			center_x;
	int32_t		x;
	int32_t		y;
	static int	i = 0;

	center_x = WIDTH / 2;
	if (i != 2)
		i++;
	else
	{
		mlx_get_mouse_pos(game->win.mlx, &x, &y);
		if (x > 0)
			game->player.angle += (x - center_x) * 0.001;
		else
			game->player.angle -= (center_x - x) * 0.001;
	}
	mlx_set_mouse_pos(game->win.mlx, center_x, HEIGHT / 2);
}

void	loop_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_keys(game);
	handle_cursor(game);
	cast_rays(game);
	draw_minimap(game);
}

void	init_events(t_game *game)
{
	mlx_set_cursor_mode(game->win.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(game->win.mlx, &loop_hook, game);
	mlx_close_hook(game->win.mlx, &mlx_close, game);
}
