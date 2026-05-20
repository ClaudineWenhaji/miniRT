/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:35:40 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/20 14:29:41 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int    setup_camera(char **split_line, t_camera *camera)
{
    t_vec   world_up;

	camera->fov = ft_atod(split_line[3]);
	if (!get_vector_from_str(split_line[1], &camera->viewpoint)
            || !get_vector_from_str(split_line[2], &camera->direction))
        return (0);
    camera->focal_length = 1.0;
    camera->forward = vec_normalize(camera->direction);
    world_up = vector(0, 1, 0);
    if (camera->forward.x == 0 && camera->forward.z == 0)
        world_up = vector(0, 0, 1);
    camera->right = vec_normalize(vec_cross_prod(camera->forward, world_up));
    camera->up = vec_cross_prod(camera->right, camera->forward);
    return (1);
}

void    setup_viewport(t_camera *camera, t_viewport *viewport, t_img *img)
{
    t_vec   center_viewport;

    if (camera == NULL || img == NULL)
        return ;
    viewport->viewport_height = 2.0 * camera->focal_length
        * tan((camera->fov * 0.5) * PI / 180.0);
    viewport->viewport_width = viewport->viewport_height
        * ((double)img->image_width / img->image_height);
    viewport->viewport_u = vec_mult(camera->right, viewport->viewport_width);
    viewport->viewport_v = vec_mult(camera->up, -viewport->viewport_height);
    viewport->pixel_delta_u = vec_mult(viewport->viewport_u,
            1.0 / (double)img->image_width);
    viewport->pixel_delta_v = vec_mult(viewport->viewport_v,
            1.0 / (double)img->image_height);
    center_viewport = vec_add(camera->viewpoint,
            vec_mult(camera->forward, camera->focal_length));
    viewport->viewport_upper_left = vec_sub(center_viewport,
            vec_add(vec_mult(viewport->viewport_u, 0.5),
                vec_mult(viewport->viewport_v, 0.5)));
    viewport->pixel_center_loc = vec_add(viewport->viewport_upper_left,
            vec_mult(vec_add(viewport->pixel_delta_u,
                    viewport->pixel_delta_v), 0.5));
}


t_ray   camera_ray(t_camera *camera, t_viewport *viewport, int pixel_x,
        int pixel_y)
{
	t_ray	ray;
    t_vec   pixel_center;

    pixel_center = vec_add(viewport->pixel_center_loc,
            vec_add(vec_mult(viewport->pixel_delta_u, (double)pixel_x),
                vec_mult(viewport->pixel_delta_v, (double)pixel_y)));
    ray.origin = camera->viewpoint;
    ray.direction = vec_normalize(vec_sub(pixel_center, camera->viewpoint));
    return (ray);
}
