/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:54:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/16 16:47:58 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "../inc/cub3d.h"

typedef struct s_bresenham_vars
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
}		t_bresenham_vars;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
}		t_line;

void	init_window(t_win *win);
void	draw_map(t_game *game);
void	draw_player(t_game *game);

void	draw_line(t_game *game, t_line line);

void	init_events(t_game *game);

void	key_hook(mlx_key_data_t key, void *param);
void	mlx_close(void *param);

void	first_hor_inter(t_game *game);
void	other_hor_inter(t_game *game);
void	first_ver_inter(t_game *game);
void	other_ver_inter(t_game *game);

void	cast_ray(t_game *game);
void	cast_rays(t_game *game);

#endif