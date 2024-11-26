/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:27:23 by yboumlak          #+#    #+#             */
/*   Updated: 2024/11/26 19:14:48 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

static double	calculate_distance(t_pos point1, t_pos point2)
{
	double	dx;
	double	dy;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	return (sqrt((dx * dx) + (dy * dy)));
}

static double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle <= 0)
		angle = 2 * M_PI + angle;
	return (angle);
}

void	update_ray_distance(t_game *game, double hor_distance,
		double ver_distance)
{
	if (hor_distance < ver_distance)
	{
		game->ray.wall_hit = game->ray.hor_inter;
		game->ray.distance = hor_distance;
		game->ray.color = 0xFFFFFFFF;
		game->ray.was_hit_vertical = false;
	}
	else
	{
		game->ray.wall_hit = game->ray.ver_inter;
		game->ray.distance = ver_distance;
		game->ray.color = 0x0000FFFF;
		game->ray.was_hit_vertical = true;
	}
}

void	cast_ray(t_game *game)
{
	double	hor_distance;
	double	ver_distance;

	hor_distance = 1000000000.0;
	ver_distance = 1000000000.0;
	init_ray(&game->ray);
	first_hor_inter(game);
	other_hor_inter(game);
	first_ver_inter(game);
	other_ver_inter(game);
	if (game->ray.found_hor_wall_hit)
		hor_distance = calculate_distance(game->player.pos_in_pix,
				game->ray.hor_inter);
	if (game->ray.found_ver_wall_hit)
		ver_distance = calculate_distance(game->player.pos_in_pix,
				game->ray.ver_inter);
	update_ray_distance(game, hor_distance, ver_distance);
}

void	cast_rays(t_game *game)
{
	double	ray_angle;
	double	ray_angle_step;
	int		i;
	double	fov;

	fov = 60 * (M_PI / 180);
	if (game->win.img)
		mlx_delete_image(game->win.mlx, game->win.img);
	game->win.img = mlx_new_image(game->win.mlx, WIDTH, HEIGHT);
	if (!game->win.img)
		exit(EXIT_FAILURE);
	draw_background(game);
	ray_angle = game->player.angle - (fov / 2);
	ray_angle_step = fov / WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		game->ray.angle = normalize_angle(ray_angle);
		cast_ray(game);
		draw_walls(game, i);
		ray_angle += ray_angle_step;
		i++;
	}
	mlx_image_to_window(game->win.mlx, game->win.img, 0, 0);
}
