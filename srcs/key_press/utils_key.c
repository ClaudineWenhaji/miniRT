/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:17:54 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/08 12:24:09 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	handle_move(int keysym, t_camera *cam, double speed)
{
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
	if (keysym == KEY_PAGE_UP)
		cam->viewpoint = vec_add(cam->viewpoint, vec_mult(cam->up, speed));
	if (keysym == KEY_PAGE_DOWN)
		cam->viewpoint = vec_sub(cam->viewpoint, vec_mult(cam->up, speed));
}

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

void	handle_rotation(int keysym, t_camera *cam)
{
	t_vec			world_up;

	world_up = vector(0, 1, 0);
	if (keysym == KEY_DIR_LEFT)
		rotate_camera(cam, world_up, 0.3);
	if (keysym == KEY_DIR_RIGHT)
		rotate_camera(cam, world_up, -0.3);
	if (keysym == KEY_DIR_DOWN)
		rotate_camera(cam, cam->right, -0.3);
	if (keysym == KEY_DIR_UP)
		rotate_camera(cam, cam->right, 0.3);
}
