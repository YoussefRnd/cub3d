/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:20:55 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/03 12:50:38 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "raycaster/raycaster.h"

void init_map(t_map *map)
{
	map->size.x = 10;
	map->size.y = 10;
	char *temp_map[10] = {
		"1111111111",
		"1000000001",
		"1110000001",
		"1000001111",
		"1000N00001",
		"1000000001",
		"1111000001",
		"1000000101",
		"1110000001",
		"1111111111"
	};
	map->grid = malloc(map->size.y * sizeof(char *));
	for (int i = 0; i < map->size.y; i++)
	{
		map->grid[i] = malloc((map->size.x + 1) * sizeof(char)); 
		strcpy(map->grid[i], temp_map[i]);
	}
}

void init_player(t_player *player)
{
	player->pos.x = 4;
	player->pos.y = 4;
	player->orientation = 'N';
}
int	main(void)
{
	t_game	game;

	init_window(&game.win);
	init_map(&game.map);
	init_player(&game.player);
	draw_map(&game);
	draw_player(&game);
	init_events(&game);
	mlx_loop(game.win.mlx);
}
