/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:35:45 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/05 18:15:21 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_phong(t_phong *p, void *obj, t_material *mat)
{
	t_texture_info	info;

	p->normal = get_normal_any(obj, p->hit_point);
	if (vec_dot(p->normal, p->ray.direction) > 0)
		p->normal = vec_mult(p->normal, -1.0);
	p->obj_color = get_object_color(obj, p->hit_point);
	if (!mat->texture)
		return (mat->emissive > 0);
	info.object = obj;
	info.material = mat;
	info.texture = mat->texture;
	p->obj_color = get_color_from_texture(
			p->normal, p->hit_point, &info);
	return (mat->emissive > 0);
}

static t_color	process_ambient(t_color color, t_ambient *amb)
{
	return (c_mult(
			c_prod(color, amb->color),
			amb->ratio));
}

static double	get_shadow_factor(t_phong *p, t_light *light)
{
	t_ray		sray;
	t_vec		dist;
	void		*obj;
	double		t;

	dist = vec_sub(light->pos, p->hit_point);
	sray.origin = vec_add(p->hit_point,
			vec_mult(p->normal, EPSILON * 2.0));
	sray.direction = vec_normalize(dist);
	obj = find_closest_point(&sray, p->scene->objects, &t);
	if (obj == p->obj)
		return (1.0);
	if (!obj || t >= vec_length(dist))
		return (1.0);
	if (get_obj_material(obj).transparency > 0)
		return (get_obj_material(obj).transparency * 0.5);
	return (0.0);
}

static t_color	process_light(t_phong *p, t_light *light)
{
	t_light_ctx	ctx;
	t_color		res;

	ctx.light = light;
	ctx.light_dir = vec_normalize(
			vec_sub(light->pos, p->hit_point));
	ctx.shadow = get_shadow_factor(p, light);
	res = (t_color){0, 0, 0};
	if (ctx.shadow <= 0.0)
		return (res);
	res = c_add(res, get_diffuse(p, &ctx));
	res = c_add(res, get_specular(p, &ctx));
	return (res);
}

t_color	phong_model(t_phong *p, t_list *lights)
{
	t_color	res;

	res = (t_color){0, 0, 0};
	if (init_phong(p, p->obj, p->material))
		return (c_mult(p->obj_color,
				p->material->emissive));
	while (lights)
	{
		if (*(t_type_light *)lights->content == AMBIENT)
			res = c_add(res,
					process_ambient(
						p->obj_color,
						(t_ambient *)lights->content));
		else
			res = c_add(res,
					process_light(
						p,
						(t_light *)lights->content));
		lights = lights->next;
	}
	return (res);
}
