/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:38:08 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/22 18:46:20 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_ray	camera_ray(t_camera *camera, t_viewport *viewport, int pixel_x,
	int pixel_y)
{
	t_ray	ray;
	t_vec	pixel_center;

	pixel_center = vec_add(viewport->pixel_center_loc,
			vec_add(vec_mult(viewport->pixel_delta_u, (double)pixel_x),
				vec_mult(viewport->pixel_delta_v, (double)pixel_y)));
	ray.origin = camera->viewpoint;
	ray.direction = vec_normalize(vec_sub(pixel_center, camera->viewpoint));
	return (ray);
}

void	render(t_scene *scene)
{
	int		pixel_x;
	int		pixel_y;
	t_ray	ray;
	t_list	*tmp_obj;
	void	*closest_obj;
	double	closest_t;
	double	t;

	pixel_y = 0;
	while (pixel_y < scene->window->img->image_height)
	{
		pixel_x = 0;
		while (pixel_x < scene->window->img->image_width)
		{
			ray = camera_ray(&scene->camera, &scene->viewport,
					pixel_x, pixel_y);
			closest_t = INFINITY;
			closest_obj = NULL;
			tmp_obj = scene->objects;
			while (tmp_obj)
			{
				if (intersect_object(tmp_obj->content, &ray, &t))
				{
					if (t < closest_t)
					{
						closest_t = t;
						closest_obj = tmp_obj->content;
					}
				}
				tmp_obj = tmp_obj->next;
			}
			put_pixel(scene->window->img, pixel_x, pixel_y,
				ray_color(scene, closest_obj, ray, closest_t));
			pixel_x++;
		}
		pixel_y++;
	}
}
