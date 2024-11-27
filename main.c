/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:20:55 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/27 07:05:51 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "inc/parsing.h"
#include "raycaster/raycaster.h"

void	draw_background(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i < HEIGHT / 2)
				mlx_put_pixel(game->win.img, j, i, game->ceiling_color);
			else
				mlx_put_pixel(game->win.img, j, i, game->floor_color);
			j++;
		}
		i++;
	}
}

void	init_map(t_map *map, int x, int y)
{
	map->size.x = x;
	map->size.y = y;
}

char	get_player_orientation(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_a_position_char(map[i][j]))
				return (map[i][j]);
			j++;
		}
		i++;
	}
	return ('N');
}

void	init_player(t_player *player, char **map)
{
	determine_player_pos(&(player->pos), map);
	player->pos_in_pix.x = player->pos.x * TILE_SIZE + (TILE_SIZE / 2);
	player->pos_in_pix.y = player->pos.y * TILE_SIZE + (TILE_SIZE / 2);
	player->orientation = get_player_orientation(map);
	if (player->orientation == 'N')
		player->angle = 270 * (M_PI / 180);
	else if (player->orientation == 'E')
		player->angle = 0;
	else if (player->orientation == 'S')
		player->angle = 90 * (M_PI / 180);
	else if (player->orientation == 'W')
		player->angle = 180 * (M_PI / 180);
}

int	main(int ac, char **av)
{
	t_game			game;
	t_components	components;

	if (ac != 3)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (-1);
	}
	if (!(parse_the_file(av[1], &components)))
		return (-1);
	game.components = &components;
	game.floor_color = get_color(components.floor_color);
	game.ceiling_color = get_color(components.ceiling_color);
	game.map.grid = list_to_array(components.map,
			get_max_string_length(components.map));
	init_window(&game.win);
	init_map(&game.map, get_max_string_length(components.map),
		get_y(components.map));
	init_player(&game.player, game.map.grid);
	draw_minimap(&game);
	draw_player(&game);
	cast_rays(&game);
	init_events(&game);
	mlx_loop(game.win.mlx);
	free_comps(&components);
}
