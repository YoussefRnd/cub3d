/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:54:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/05 13:26:14 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "../inc/cub3d.h"

void	init_window(t_win *win);
void	draw_map(t_game *game);
void	draw_player(t_game *game);

void	init_events(t_game *game);

void	key_hook(mlx_key_data_t key, void *param);
void	mlx_close(void *param);

#endif