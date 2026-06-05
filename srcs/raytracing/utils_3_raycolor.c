/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_raycolor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:19:32 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/05 18:23:14 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_refract_ctx(t_ray_ctx *c,
				t_ray ray)
{
	c->refract.incident = ray.direction;
	c->refract.normal = c->normal;
	c->refract.hit_point = c->hit_point;
	c->refract.ior_in = c->ior;
	c->refract.ior_out = c->mat.ior;
}

t_ray	calculate_refract(t_refract *r)
{
	double	cos_i;
	double	eta;
	t_ray	ray;
	double	k;

	cos_i = fmin(vec_dot(vec_mult(r->incident, -1.0), r->normal), 1.0);
	eta = r->ior_out / r->ior_in;
	if (vec_dot(r->incident, r->normal) > 0)
	{
		eta = r->ior_in / r->ior_out;
		r->normal = vec_mult(r->normal, -1.0);
		cos_i = fmin(vec_dot(vec_mult(r->incident, -1.0), r->normal), 1.0);
	}
	k = 1.0 - eta * eta * (1.0 - cos_i * cos_i);
	if (k < 0)
	{
		ray.direction = vector(0, 0, 0);
		return (ray);
	}
	ray.origin = vec_sub(r->hit_point, vec_mult(r->normal, EPSILON * 2.0));
	ray.direction = vec_normalize(vec_add(vec_mult(r->incident, eta),
				vec_mult(r->normal, (eta * cos_i - sqrt(k)))));
	return (ray);
}
