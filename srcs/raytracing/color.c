/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:35:02 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/22 18:47:42 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = ft_clamp((int)color.red, 0, 255);
	g = ft_clamp((int)color.green, 0, 255);
	b = ft_clamp((int)color.blue, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

static t_vec	get_normal(void *obj, t_vec hit_point, t_color *obj_color)
{
	t_vec	normal;

	if (*(t_type *)obj == SPHERE)
	{
		normal = vec_normalize(
				vec_sub(hit_point, ((t_sphere *)obj)->center));
		*obj_color = ((t_sphere *)obj)->color;
	}
	else if (*(t_type *)obj == PLANE)
	{
		normal = vec_normalize(((t_plane *)obj)->normal);
		*obj_color = ((t_plane *)obj)->color;
	}
	else if (*(t_type *)obj == CYLINDER)
	{
		normal = get_normal_cylinder((t_cylinder *)obj, hit_point);
		*obj_color = ((t_cylinder *)obj)->color;
	}
	else if (*(t_type *)obj == CONE)
	{
		normal = get_normal_cone(((t_cone *)obj), hit_point);
		*obj_color = ((t_cone *)obj)->color;
	}
	else
		normal = vector(0, 1, 0);
	return (normal);
}

int	ray_color(t_scene *scene, void *obj, t_ray ray, double t)
{
	t_vec				hit_point;
	t_vec				normal;
	t_vec				light_dir;
	double				intensity;
	t_color				final_color;
	t_color				obj_color;
	t_list				*light_node;
	double				a;
	t_color				sky;
	t_light				*l;
	double				diffuse;
	t_type_light		type;

	if (!obj)
	{
		a = 0.5 * (ray.direction.y + 1.0);
		sky.red = ((1.0 - a) * 1.0 + a * 0.5) * 255.0;
		sky.green = ((1.0 - a) * 1.0 + a * 0.7) * 255.0;
		sky.blue = ((1.0 - a) * 1.0 + a * 1.0) * 255.0;
		return (color_to_int(sky));
	}
	intensity = 0.0;
	hit_point = vec_add(ray.origin, vec_mult(ray.direction, t));
	normal = get_normal(obj, hit_point, &obj_color);
	if (vec_dot(normal, ray.direction) > 0)
		normal = vec_mult(normal, -1);
	light_node = scene->lights;
	while (light_node)
	{
		type = *(t_type_light *)light_node->content;
		if (type == AMBIENT)
			intensity += ((t_ambient *)light_node->content)->ratio;
		else if (type == LIGHT)
		{
			l = (t_light *)light_node->content;
			light_dir = vec_normalize(vec_sub(l->pos, hit_point));
			diffuse = vec_dot(normal, light_dir);
			if (diffuse > 0)
				intensity += diffuse * l->brightness;
		}
		light_node = light_node->next;
	}
	if (intensity > 1.0)
		intensity = 1.0;
	final_color.red = obj_color.red * intensity;
	final_color.green = obj_color.green * intensity;
	final_color.blue = obj_color.blue * intensity;
	return (color_to_int(final_color));
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->data
		+ (y * img->size_line)
		+ (x * (img->bit_per_pixel / 8));
	*(unsigned int *)dest = color;
}
