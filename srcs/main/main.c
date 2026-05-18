/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:19:44 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/18 18:25:35 by clwenhaj         ###   ########.fr       */
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
		img_tmp->img_ptr = mlx_new_image(mlx, WINDOWS_WIDTH, WINDOWS_HEIGHT);
		if (!img_tmp->img_ptr)
			return (free(img_tmp), 0);
		img_tmp->data = mlx_get_data_addr(img_tmp->img_ptr,
				&(img_tmp->bit_per_pixel), &(img_tmp->size_line),
				&(img_tmp->endian));
	}
	total_bytes = WINDOWS_HEIGHT * img_tmp->size_line;
	ft_memset(img_tmp->data, bytes, total_bytes);
	*img = img_tmp;
	return (1);
}

static int	inits(t_scene *scene, char *name)
{
	scene->window = (t_win *)malloc(sizeof(t_win));
	if (!scene->window)
		return (printf("Error\n"), 0);
	scene->window->mlx = mlx_init();
	if (!scene->window->mlx)
		return (printf("Error\n"), 0);
	scene->window->img = NULL;
	if (!init_img_with_color(scene->window->mlx, &scene->window->img,
				0))
		return (printf("Error\n"), 0);
	scene->window->win = mlx_new_window(scene->window->mlx, WINDOWS_WIDTH,
			WINDOWS_HEIGHT, name);
	if (!scene->window->win)
		return (printf("Error\n"), 0);
	if (!parsing(name, scene))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	t_data	data;

	if (argc != 2)
		return (printf("Usage: ./minirt <SCENE.rt>\n"), 1);
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (printf("Error\n"), 1);
	//scene->objects = NULL;
	//scene->lights = NULL;
	if (!inits(scene, argv[1]))
		return (ft_clean(&scene), 1);
	data.scene = scene;
	data.camera = scene->camera;
	setup_camera(&data.camera);
	render(&data);
	mlx_put_image_to_window(scene->window->mlx, scene->window->win,
			scene->window->img->img_ptr, 0, 0);
	mlx_loop(scene->window->mlx);
	return (ft_clean(&scene), 0);
}
