/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:44:53 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/02 15:40:17 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_root(t_quad q, double *root)
{
	*root = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	if (*root < EPSILON)
	{
		*root = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
		if (*root < EPSILON)
			return (0);
	}
	return (1);
}

int	intersect_sphere(t_sphere *sphere, t_ray *ray, double *t)
{
	t_vec	oc;
	t_quad	q;
	double	root;

	oc = vec_sub(ray->origin, sphere->center);
	q.a = vec_dot(ray->direction, ray->direction);
	q.b = 2.0 * vec_dot(oc, ray->direction);
	q.c = vec_dot(oc, oc) - (sphere->radius * sphere->radius);
	if (fabs(q.a) < EPSILON)
		return (0);
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	if (q.discriminant < 0 || !get_root(q, &root))
		return (0);
	if (t)
		*t = root;
	return (1);
}
