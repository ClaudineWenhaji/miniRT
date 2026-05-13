/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:35:40 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/13 15:39:53 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    setup_camera(t_camera *camera)
{
    t_vec   world_up;
    
    camera->forward = vec_normalize(camera->direction);
    world_up = (t_vec){0,1,0};
    if (fabs(camera->forward.y) > 0.999)
        world_up = (t_vec){0,0,1};
    camera->right = vec_normalize(vec_cross_prod(camera->forward, world_up));
    camera->up = vec_cross_prod(camera->right, camera->forward);
}

t_ray   camera_ray(t_camera *camera, int x, int y)
{
	t_ray	ray;
	double	aspect;
	double	scale;
	double	px;
	double	py;
	t_vec	direction;

	aspect = (double)WINDOWS_WIDTH / (double)WINDOWS_HEIGTH;
    scale = tan((camera->fov * 0.5) * PI / 180.0);
    px = (x + 0.5) / (double)WINDOWS_WIDTH;
    py = (y + 0.5) / (double)WINDOWS_HEIGTH;
    px = (2 * px) * aspect * scale;
    py = (1 - (2 * py)) * scale;
    direction = camera->forward + vec_add(vec_scale(camera->right,px), vec_scale(camera->up,py));
    ray->origin = camera->viewpoint;
    direction = vec_normalize(direction);
    return (ray);
}
