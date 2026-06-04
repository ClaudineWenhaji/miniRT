/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:38:08 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/04 13:46:44 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
