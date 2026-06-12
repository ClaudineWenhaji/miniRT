/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycolor_algorithm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:19:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/06/11 18:33:31 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_ray_ctx(t_ray_ctx *c, t_scene *scene, t_ray ray)
{
	c->p.scene = scene;
	c->p.ray = ray;
	c->object = find_closest_point(&ray, scene->objects, &c->t);
	if (!c->object)
		return (0);
	c->mat = get_obj_material(c->object);
	c->hit_point = vec_add(ray.origin,
			vec_mult(ray.direction, c->t));
	c->p.obj = c->object;
	c->p.material = &c->mat;
	c->p.hit_point = c->hit_point;
	return (1);
}

static t_color	compute_reflection(t_scene *scene,
				t_ray_ctx *c,
				t_ray ray,
				int depth)
{
	t_ray	r_ray;
	t_vec	r_dir;

	if (c->mat.k_spec <= 0)
		return ((t_color){0, 0, 0});
	r_dir = vec_normalize(vec_sub(ray.direction,
				vec_mult(c->normal,
					2.0 * vec_dot(c->normal,
						ray.direction))));
	r_ray = (t_ray){
		vec_add(c->hit_point,
			vec_mult(c->normal, EPSILON * 2.0)),
		r_dir
	};
	return (ray_color_recursive(scene,
			r_ray, depth + 1, c->ior));
}

static t_color	compute_refraction(t_scene *scene,
				t_ray_ctx *c,
				t_ray ray,
				int depth)
{
	if (c->mat.transparency == 0)
		return ((t_color){0, 0, 0});
	init_refract_ctx(c, ray);
	c->re_ray = calculate_refract(&c->refract);
	if (vec_length(c->re_ray.direction) == 0.0)
		return ((t_color){0, 0, 0});
	return (ray_color_recursive(scene,
			c->re_ray,
			depth + 1,
			c->mat.ior));
}

static t_color	combine_colors(t_ray_ctx *c,
				t_color reflection,
				t_color refraction)
{
	t_color	final;

	final = c_add(
			c_mult(c->local, (1.0 - c->mat.transparency)),
			c_mult(refraction, c->mat.transparency));
	final = c_add(final,
			c_mult(reflection, c->mat.k_spec));
	final = c_add(final, c->p.specular);
	return (final);
}

t_color	ray_color_recursive(t_scene *scene, t_ray ray,
			int depth, double ior)
{
	t_ray_ctx	c;
	t_color		reflection;
	t_color		refraction;

	if (depth >= MAX_DEPTH)
		return ((t_color){0, 0, 0});
	if (!init_ray_ctx(&c, scene, ray))
		return (default_color(scene));
	c.ior = ior;
	c.local = phong_model(&c.p, scene->lights);
	if (c.mat.transparency <= 0 && c.mat.k_spec <= 0)
		return (c.local);
	c.normal = get_normal_any(c.object, c.hit_point);
	reflection = compute_reflection(scene, &c, ray, depth);
	refraction = compute_refraction(scene, &c, ray, depth);
	return (combine_colors(&c, reflection, refraction));
}
