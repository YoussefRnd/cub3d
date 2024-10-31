/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 04:48:05 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/31 05:59:12 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_on_textures(t_game *game)
{
	float texture_x;
	float texture_y;
	if (!game->ray.was_hit_vertical)
		texture_x = ((int)game->ray.hor_inter.x % TILE_SIZE)
			* (game->components->east_texture->width / TILE_SIZE);
	else
		texture_x = (((int)game->ray.ver_inter.y % TILE_SIZE)
				* (game->components->north_texture->width / TILE_SIZE));
    
}