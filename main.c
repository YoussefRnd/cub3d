/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:20:55 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/29 08:27:32 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "inc/parsing.h"
#include "raycaster/raycaster.h"

void draw_background(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i < HEIGHT / 2)
				mlx_put_pixel(game->win.img, j, i, 0x00FFFFFF);
			else
				mlx_put_pixel(game->win.img, j, i, 0x000000FF);
			j++;
		}
		i++;
	}
}

void	init_map(t_map *map,int x,int y)
{
	map->size.x = x;
	map->size.y = y;
}


char	get_player_orientation(t_mapp *map)
{
	int i = 0;

	while(map)
	{
		i = 0;
		while(map->line[i])
		{
			if (is_a_position_char(map->line[i]))
				return map->line[i];
			i++;
		}
		map = map->next;
	}
	return 'N';
}

void	init_player(t_player *player, char **map)
{
	determine_player_pos(&(player->pos), map);
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

int get_y(t_mapp *head)
{
	int height = 0;
	while (head)
	{
		height++;
		head = head->next;
	}
	return height;
}

int	main(int ac, char **av)
{
	t_game	game;
	t_components comps;

	(void)ac;
	if (!(parse_the_file(av[1], &comps)))
		return -1;
	game.map.grid = list_to_array(comps.map, get_max_string_length(comps.map));
	init_window(&game.win);
	init_map(&game.map, get_max_string_length(comps.map), get_y(comps.map));
	init_player(&game.player, game.map.grid);
	draw_map(&game);
	draw_player(&game);
	cast_rays(&game);
	init_events(&game);
	mlx_loop(game.win.mlx);
}
