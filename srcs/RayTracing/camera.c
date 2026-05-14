/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:35:40 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/14 09:30:01 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    setup_camera(t_camera *camera)
{
    t_vec   world_up;
    
    camera->forward = vec_normalize(camera->direction);
    world_up = vector(0,1,0);
    if (fabs(camera->forward.y) > 0.999)
        world_up = vector(0,0,1);
    camera->right = vec_normalize(vec_cross_prod(camera->forward, world_up));
    camera->up = vec_cross_prod(camera->right, camera->forward);
}

t_ray   camera_ray(t_camera *camera, int pixel_x, int pixel_y)
{
	t_ray	ray;
	double	aspect;
	double	scale;
	double	px;
	double	py;

	aspect = (double)WINDOWS_WIDTH / (double)WINDOWS_HEIGHT;
    scale = tan((camera->fov * 0.5) * PI / 180.0);
    // plan image avec le centre du pixel [0, 1]
    px = (pixel_x + 0.5) / (double)WINDOWS_WIDTH;
    py = (pixel_y + 0.5) / (double)WINDOWS_HEIGHT;
    // Ecran [-1, 1]
    px = ((2.0 * px) - 1) * aspect * scale;
    py = (1.0 - (2.0 * py)) * scale;
    ray.direction = vec_add(
        camera->forward,
        vec_add(
            vec_mult(camera->right,px),
            vec_mult(camera->up,py)));
    ray.direction = vec_normalize(ray.direction);
    ray.origin = camera->viewpoint;
    return (ray);
}
