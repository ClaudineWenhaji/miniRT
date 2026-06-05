/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_raycolor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:34:43 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/05 18:18:19 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_material	get_obj_material(void *object)
{
	if (*(t_type *)object == SPHERE)
		return (((t_sphere *)object)->material);
	if (*(t_type *)object == CYLINDER)
		return (((t_cylinder *)object)->material);
	if (*(t_type *)object == CONE)
		return (((t_cone *)object)->material);
	if (*(t_type *)object == PLANE)
		return (((t_plane *)object)->material);
	return ((t_material){{0, 0, 0}, 1, 0, 1, 1, 0, 1, 0,
		NULL, {0, 0, 0}, {0, 0, 0}, 0});
}

t_color	get_object_color(void *object, t_point hit_point)
{
	t_material	mat;

	mat = get_obj_material(object);
	if (!mat.is_checkerboard)
		return (mat.color);
	if (*(t_type *)object == PLANE)
		return (checker_plane((t_plane *)object, &mat, hit_point));
	if (*(t_type *)object == SPHERE)
		return (checker_sphere((t_sphere *)object, &mat, hit_point));
	if (*(t_type *)object == CYLINDER)
		return (checker_cylinder((t_cylinder *)object, &mat, hit_point));
	if (*(t_type *)object == CONE)
		return (checker_cone((t_cone *)object, &mat, hit_point));
	return (mat.color);
}

t_vec	get_normal_any(void *obj, t_point hit_point)
{
	t_type	type;

	type = *(t_type *)obj;
	if (type == SPHERE)
		return (vec_normalize(vec_sub(hit_point, ((t_sphere *)obj)->center)));
	if (type == PLANE)
		return (vec_normalize(((t_plane *)obj)->normal));
	if (type == CYLINDER)
		return (get_normal_cylinder((t_cylinder *)obj, hit_point));
	if (type == CONE)
		return (get_normal_cone((t_cone *)obj, hit_point));
	return (vector(0, 1, 0));
}

t_color	default_color(t_scene *scene)
{
	t_list		*light;
	t_ambient	*amb;

	light = scene->lights;
	while (light)
	{
		if (*(t_type_light *)light->content == AMBIENT)
		{
			amb = (t_ambient *)light->content;
			return (c_mult(amb->color, amb->ratio));
		}
		light = light->next;
	}
	return ((t_color){0.0, 0.0, 0.0});
}

void	*find_closest_point(t_ray *ray, t_list *objects, double *t_out)
{
	double	closest_t;
	double	t;
	t_list	*node;
	void	*closest_object;

	closest_t = INFINITY;
	node = objects;
	closest_object = NULL;
	while (node)
	{
		if (intersect_object(node->content, ray, &t))
		{
			if (t > EPSILON && t < closest_t)
			{
				closest_t = t;
				closest_object = node->content;
			}
		}
		node = node->next;
	}
	*t_out = closest_t;
	return (closest_object);
}
