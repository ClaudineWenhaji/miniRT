/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:19:44 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/20 18:41:08 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_img_with_color(void *mlx, t_img **img, char bytes)
{
	t_img	*img_tmp;
	int		total_bytes;

	img_tmp = *img;
	(void)bytes;
	if (img_tmp == NULL)
	{
		img_tmp = (t_img *)malloc(sizeof(t_img));
		if (!img_tmp)
			return (0);
		img_tmp->aspect_ratio = 16.0 / 9.0;
		img_tmp->image_width = WINDOWS_WIDTH; // Change for different width
		img_tmp->image_height = (int)((double)img_tmp->image_width / img_tmp->aspect_ratio);
		if (img_tmp->image_height < 1)
			img_tmp->image_height = 1;
		img_tmp->img_ptr = mlx_new_image(mlx, img_tmp->image_width, img_tmp->image_height);
		if (!img_tmp->img_ptr)
			return (free(img_tmp), 0);
		img_tmp->data = mlx_get_data_addr(img_tmp->img_ptr,
				&(img_tmp->bit_per_pixel), &(img_tmp->size_line),
				&(img_tmp->endian));
	}
	total_bytes = img_tmp->image_height * img_tmp->size_line;
	ft_memset(img_tmp->data, bytes, total_bytes);
	*img = img_tmp;
	return (1);
}

static int	inits(t_scene *scene, char *name)
{
	scene->window = (t_win *)malloc(sizeof(t_win));
	if (!scene->window)
		return (printf("Error\nMalloc window failed"), 0);
	scene->window->mlx = mlx_init();
	if (!scene->window->mlx)
		return (printf("Error\nMlx init failed"), 0);
	scene->window->win = mlx_new_window(scene->window->mlx, WINDOWS_WIDTH,
			WINDOWS_HEIGHT, name);
	if (!scene->window->win)
		return (printf("Error\nWindow creation failed"), 0);
	scene->window->img = NULL;
	if (!init_img_with_color(scene->window->mlx, &scene->window->img,
				0))
		return (printf("Error\nImage init failed"), 0);
	
	if (!parsing(name, scene))
		return (0);
	print_scene_info(scene);
	setup_viewport(&scene->camera, &scene->viewport, scene->window->img);
	return (1);
}

static int	close_window(t_scene *scene)
{
	ft_clean(&scene);
	exit (0);
	return (0);
}

static int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
		close_window(scene);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		return (printf("Usage: ./minirt <SCENE.rt>\n"), 1);
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (printf("Error\nMalloc scene failed"), 1);
	scene->objects = NULL;
	scene->lights = NULL;
	if (!inits(scene, argv[1]))
		return (ft_clean(&scene), 1);
	render(scene);
	mlx_put_image_to_window(scene->window->mlx, scene->window->win,
			scene->window->img->img_ptr, 0, 0);
	mlx_key_hook(scene->window->win, key_hook, scene);
	mlx_hook(scene->window->win, 17, 0, close_window, scene);
	mlx_loop(scene->window->mlx);
	return (ft_clean(&scene), 0);
}
