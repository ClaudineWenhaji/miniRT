/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:32:58 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/05 18:33:29 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	camera_ray(t_camera *camera, t_viewport *viewport,
		int pixel_x, int pixel_y)
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

int	ray_color(t_scene *scene, t_ray ray)
{
	t_color	res;

	res = ray_color_recursive(scene, ray, 0, 1.0);
	return (color_to_int_local(res));
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x >= 0 && x < img->image_width && y >= 0 && y < img->image_height)
	{
		dest = img->data
			+ (y * img->size_line)
			+ (x * (img->bit_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}
