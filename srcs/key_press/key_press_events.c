/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:43:55 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/06/08 12:24:47 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static	void	update_camera_vectors(t_camera *cam)
{
	t_vec	world_up;

	cam->forward = vec_normalize(cam->direction);
	if (fabs(cam->forward.y) > 0.99)
		world_up = (t_vec){0, 0, 1};
	else
		world_up = (t_vec){0, 1, 0};
	cam->right = vec_normalize(vec_cross_prod(cam->forward, world_up));
	cam->up = vec_cross_prod(cam->right, cam->forward);
}

static	void	refresh_scene(t_scene *scene)
{
	update_camera_vectors(&scene->camera);
	setup_viewport(&scene->camera, &scene->viewport, scene->window->img);
	render(scene);
	mlx_put_image_to_window(scene->window->mlx, scene->window->win,
		scene->window->img->img_ptr, 0, 0);
}

int	handle_keypress(int keysym, void *param)
{
	t_scene			*scene;
	t_camera		*cam;
	static t_camera	camera_save;
	static int		is_init;

	scene = (t_scene *)param;
	if (!is_init)
	{
		camera_save = scene->camera;
		is_init = 1;
	}
	cam = &scene->camera;
	if (keysym == KEY_ESC)
		exit_program(param);
	handle_move(keysym, cam, 2.0);
	handle_rotation(keysym, cam);
	if (keysym == KEY_R)
		*cam = camera_save;
	if (keysym == KEY_I)
		cam->direction = vec_mult(cam->direction, -1.0);
	refresh_scene(scene);
	return (0);
}
