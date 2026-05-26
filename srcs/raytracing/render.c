/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:38:08 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/26 08:36:17 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render(t_scene *scene)
{
	int		pixel_x;
	int		pixel_y;
	t_ray	ray;

	pixel_y = 0;
	while (pixel_y < scene->window->img->image_height)
	{
		pixel_x = 0;
		while (pixel_x < scene->window->img->image_width)
		{
			ray = camera_ray(&scene->camera, &scene->viewport,
					pixel_x, pixel_y);
			put_pixel(scene->window->img, pixel_x, pixel_y,
				ray_color(scene, ray));
			pixel_x++;
		}
		pixel_y++;
	}
}
