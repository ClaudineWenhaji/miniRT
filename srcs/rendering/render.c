/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:38:08 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/05 18:51:28 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_next_tile(t_render_config *data)
{
	int	tile_to_do;

	pthread_mutex_lock(&data->mutex_r);
	tile_to_do = data->next_tile_id;
	data->next_tile_id++;
	pthread_mutex_unlock(&data->mutex_r);
	if (tile_to_do >= data->total_tiles)
		return (-1);
	return (tile_to_do);
}

static void	render_bloc(t_scene *scene, int x_start, int y_start,
		int x_end, int y_end)
{
	int		pixel_x;
	int		pixel_y;
	t_ray	ray;

	pixel_y = y_start;
	while (pixel_y < y_end)
	{
		pixel_x = x_start;
		while (pixel_x < x_end)
		{
			ray = camera_ray(&scene->camera, &scene->viewport,
					pixel_x, pixel_y);
			put_pixel(scene->window->img, pixel_x, pixel_y,
				ray_color(scene, ray));
			pixel_x++;
		}
		pixel_y++;
	}
}

static	void	*thread_routine(void *arg)
{
	t_render_config	*config;
	int				tile_id;
	int				tile_x;
	int				tile_y;
	int				x_end;
	int				y_end;

	config = (t_render_config *)arg;
	tile_id = get_next_tile(config);
	while (tile_id >= 0)
	{
		tile_x = (tile_id % config->tiles_across) * config->tiles_size;
		tile_y = (tile_id / config->tiles_across) * config->tiles_size;
		x_end = (int)fmin(tile_x + config->tiles_size,
				config->scene->window->img->image_width);
		y_end = (int)fmin(tile_y + config->tiles_size,
				config->scene->window->img->image_height);
		render_bloc(config->scene, tile_x, tile_y, x_end, y_end);
		tile_id = get_next_tile(config);
	}
	return (NULL);
}

void	render(t_scene *scene)
{
	t_render_config	config;
	pthread_t		threads[NUM_THREADS];
	int				i;

	config.scene = scene;
	config.tiles_size = SIZE_TILES;
	config.tiles_across = ceil((double)scene->window->img->image_width
			/ SIZE_TILES);
	config.total_tiles = config.tiles_across
		* ceil((double)scene->window->img->image_height / SIZE_TILES);
	config.next_tile_id = 0;
	if (pthread_mutex_init(&config.mutex_r, NULL) != 0)
	{
		printf("Error\nfail to initialize a mutex\n");
		return ;
	}
	i = -1;
	while (++i < NUM_THREADS)
		if (pthread_create(&threads[i], NULL, thread_routine, &config) != 0)
			(printf("Error\nfail to initialize threads"), ft_clean(&scene),
				exit(1));
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&config.mutex_r);
}
