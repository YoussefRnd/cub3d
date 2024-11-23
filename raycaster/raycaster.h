/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:54:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/23 21:24:07 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "../inc/cub3d.h"

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
}		t_line;

void	init_window(t_win *win);
void	init_events(t_game *game);
void	init_ray(t_ray *ray);

void	draw_background(t_game *game);
void	draw_minimap(t_game *game);
void	draw_player(t_game *game);
void	draw_line(t_game *game, t_line line);
void	draw_direction_line(t_game *game);
void	draw_walls(t_game *game, int i);

int		is_collision(t_game *game, t_pos next_pos);
t_pos	calculate_next_position(t_game *game, t_pos current_pos);

void	first_hor_inter(t_game *game);
void	other_hor_inter(t_game *game);
void	first_ver_inter(t_game *game);
void	other_ver_inter(t_game *game);

void	cast_ray(t_game *game);
void	cast_rays(t_game *game);

#endif