/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:43:55 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/06/05 18:48:54 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotate_camera(t_camera *cam, t_vec axis, double angle)
{
	t_vec	v;
	t_vec	k;
	double	cos_a;
	double	sin_a;

	v = cam->direction;
	k = axis;
	cos_a = cos(angle);
	sin_a = sin(angle);
	cam->direction = vec_normalize(vec_add(vec_add(vec_mult(v, cos_a),
					vec_mult(vec_cross_prod(k, v), sin_a)),
				vec_mult(k, vec_dot(k, v) * (1 - cos_a))));
}

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

int	handle_keypress(int keysym, void *param)
{
	t_scene			*scene;
	double			speed;
	t_camera		*cam;
	t_vec			world_up;
	static t_camera	camera_save;
	static int		is_init;

	scene = (t_scene *)param;
	if (!is_init)
	{
		camera_save = scene->camera;
		is_init = 1;
	}
	cam = &scene->camera;
	speed = 2.0;
	world_up = vector(0, 1, 0);
	if (keysym == KEY_ESC)
		exit_program(param);
	if (keysym == KEY_W)
		cam->viewpoint = vec_add(cam->viewpoint,
				vec_mult(cam->direction, speed));
	if (keysym == KEY_S)
		cam->viewpoint = vec_sub(cam->viewpoint,
				vec_mult(cam->direction, speed));
	if (keysym == KEY_A)
		cam->viewpoint = vec_sub(cam->viewpoint, vec_mult(cam->right, speed));
	if (keysym == KEY_D)
		cam->viewpoint = vec_add(cam->viewpoint, vec_mult(cam->right, speed));
	if (keysym == KEY_DIR_LEFT)
		rotate_camera(cam, world_up, 0.3);
	if (keysym == KEY_DIR_RIGHT)
		rotate_camera(cam, world_up, -0.3);
	if (keysym == KEY_DIR_DOWN)
		rotate_camera(cam, cam->right, -0.3);
	if (keysym == KEY_DIR_UP)
		rotate_camera(cam, cam->right, 0.3);
	if (keysym == KEY_PAGE_UP)
		cam->viewpoint = vec_add(cam->viewpoint, vec_mult(cam->up, speed));
	if (keysym == KEY_PAGE_DOWN)
		cam->viewpoint = vec_sub(cam->viewpoint, vec_mult(cam->up, speed));
	if (keysym == KEY_R)
		*cam = camera_save;
	if (keysym == KEY_I)
		cam->direction = vec_mult(cam->direction, -1.0);
	update_camera_vectors(cam);
	setup_viewport(cam, &scene->viewport, scene->window->img);
	render(scene);
	mlx_put_image_to_window(scene->window->mlx, scene->window->win,
		scene->window->img->img_ptr, 0, 0);
	return (0);
}
