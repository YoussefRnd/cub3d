/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:27:23 by yboumlak          #+#    #+#             */
/*   Updated: 2024/10/22 18:18:08 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "raycaster.h"

double	calculate_distance(t_pos point1, t_pos point2)
{
	double	dx;
	double	dy;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	return (sqrt((dx * dx) + (dy * dy)));
}
double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle <= 0)
		angle = 2 * M_PI + angle;
	return (angle);
}

void	cast_ray(t_game *game)
{
	double	hor_distance;
	double	ver_distance;
	bool	found_hor_wall_hit;
	bool	found_ver_wall_hit;

	hor_distance = 0;
	ver_distance = 0;
	found_hor_wall_hit = false;
	found_ver_wall_hit = false;
	game->ray.is_facing_down = game->ray.angle > 0 && game->ray.angle < M_PI;
	game->ray.is_facing_up = !game->ray.is_facing_down;
	game->ray.is_facing_right = game->ray.angle < 0.5 * M_PI
		|| game->ray.angle > 1.5 * M_PI;
	game->ray.is_facing_left = !game->ray.is_facing_right;
	game->ray.hor_inter = (t_pos){0, 0};
	game->ray.ver_inter = (t_pos){0, 0};
	game->ray.wall_hit = (t_pos){0, 0};
	first_hor_inter(game);
	double xa, ya;
	if (game->ray.is_facing_up)
		ya = -TILE_SIZE;
	else
		ya = TILE_SIZE;
	xa = ya / tan(game->ray.angle);
	while (game->ray.hor_inter.x >= 0
		&& game->ray.hor_inter.x < game->map.size.x * TILE_SIZE
		&& game->ray.hor_inter.y >= 0
		&& game->ray.hor_inter.y < game->map.size.y * TILE_SIZE)
	{
		if (game->map.grid[(int)(game->ray.hor_inter.y
				/ TILE_SIZE)][(int)(game->ray.hor_inter.x / TILE_SIZE)] == '1')
		{
			found_hor_wall_hit = true;
			break ;
		}
		else
		{
			game->ray.hor_inter.x += xa;
			game->ray.hor_inter.y += ya;
		}
	}
	first_ver_inter(game);
	double xb, yb;
	if (game->ray.is_facing_right)
		xb = TILE_SIZE;
	else
		xb = -TILE_SIZE;
	yb = xb * tan(game->ray.angle);
	while (game->ray.ver_inter.x >= 0
		&& game->ray.ver_inter.x < game->map.size.x * TILE_SIZE
		&& game->ray.ver_inter.y >= 0
		&& game->ray.ver_inter.y < game->map.size.y * TILE_SIZE)
	{
		if (game->map.grid[(int)(game->ray.ver_inter.y
				/ TILE_SIZE)][(int)(game->ray.ver_inter.x / TILE_SIZE)] == '1')
		{
			found_ver_wall_hit = true;
			break ;
		}
		else
		{
			game->ray.ver_inter.x += xb;
			game->ray.ver_inter.y += yb;
		}
	}
	if (found_hor_wall_hit)
		hor_distance = calculate_distance(game->player.pos_in_pix,
				game->ray.hor_inter);
	else
		hor_distance = 1000000000.0;
	if (found_ver_wall_hit)
		ver_distance = calculate_distance(game->player.pos_in_pix,
				game->ray.ver_inter);
	else
		ver_distance = 1000000000.0;
	if (hor_distance < ver_distance)
	{
		game->ray.wall_hit.x = game->ray.hor_inter.x;
		game->ray.wall_hit.y = game->ray.hor_inter.y;
		game->ray.distance = hor_distance;
	}
	else
	{
		game->ray.wall_hit.x = game->ray.ver_inter.x;
		game->ray.wall_hit.y = game->ray.ver_inter.y;
		game->ray.distance = ver_distance;
	}
	// draw_line(game, (t_line){game->player.pos_in_pix.x * MINIMAP_SCALE,
	// 	game->player.pos_in_pix.y * MINIMAP_SCALE, game->ray.wall_hit.x
	// 	* MINIMAP_SCALE, game->ray.wall_hit.y * MINIMAP_SCALE, 0x00FF00FF});
}

void	draw_walls(t_game *game, int i)
{
	double	distance_proj_plane;
	double	wall_strip_height;
	double	start;
	double	end;
	double	ray_distance;

	ray_distance = game->ray.distance * cos(game->ray.angle
			- game->player.angle);
	distance_proj_plane = (WIDTH / 2) / tan(FOV / 2);
	wall_strip_height = (TILE_SIZE / ray_distance) * distance_proj_plane;
	start = (HEIGHT / 2) - (wall_strip_height / 2);
	end = (HEIGHT / 2) + (wall_strip_height / 2);
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (start < end)
	{
		mlx_put_pixel(game->win.img, i, start, WALL_COLOR);
		start++;
	}
}

void	cast_rays(t_game *game)
{
	double	ray_angle;
	double	ray_angle_step;
	int		i;

	game->win.img = mlx_new_image(game->win.mlx, WIDTH, HEIGHT);
	if (!game->win.img)
		exit(EXIT_FAILURE);
	ray_angle = game->player.angle - (FOV / 2);
	ray_angle_step = FOV / WIDTH;
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
