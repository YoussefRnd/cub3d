/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:20:55 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/22 13:30:32 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "raycaster/raycaster.h"

void	init_map(t_map *map)
{
	char	*temp_map[10] = {"1111111111", "1000001001", "1110000101",
			"1000001111", "1000N00001", "1000000001", "1111000001",
			"1000000101", "1110000001", "1111111111"};

	map->size.x = 10;
	map->size.y = 10;
	map->grid = malloc(map->size.y * sizeof(char *));
	for (int i = 0; i < map->size.y; i++)
	{
		map->grid[i] = malloc((map->size.x + 1) * sizeof(char));
		strcpy(map->grid[i], temp_map[i]);
	}
}

void	init_player(t_player *player)
{
	player->pos.x = 4;
	player->pos.y = 4;
	player->pos_in_pix.x = player->pos.x * TILE_SIZE + (TILE_SIZE / 2);
	player->pos_in_pix.y = player->pos.y * TILE_SIZE + (TILE_SIZE / 2);
	player->orientation = 'N';
	if (player->orientation == 'N')
		player->angle = 270 * (M_PI / 180);
	else if (player->orientation == 'E')
		player->angle = 0;
	else if (player->orientation == 'S')
		player->angle = 90 * (M_PI / 180);
	else if (player->orientation == 'W')
		player->angle = 180 * (M_PI / 180);
}
int	main(void)
{
	t_game	game;

	init_window(&game.win);
	init_map(&game.map);
	init_player(&game.player);
	draw_map(&game);
	draw_player(&game);
	cast_rays(&game);
	init_events(&game);
	mlx_loop(game.win.mlx);
}
