/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:12:51 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/01 14:11:43 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	intersect_disk(t_cone *cone, t_ray *ray, double *t)
{
	t_vec	disk_center;
	double	t_solution;
	t_vec	vec_diff;
	double	radius;

	disk_center = vec_add(cone->apex, vec_mult(cone->axis, cone->height));
	if (fabs(vec_dot(ray->direction, cone->axis)) < EPSILON)
		return (0);
	t_solution = vec_dot(vec_sub(disk_center, ray->origin), cone->axis)
		/ vec_dot(ray->direction, cone->axis);
	if (t_solution < EPSILON)
		return (0);
	vec_diff = vec_sub(vec_add(ray->origin,
				vec_mult(ray->direction, t_solution)), disk_center);
	radius = cone->height * tan(cone->angle * PI / 180.0);
	if (vec_dot(vec_diff, vec_diff) > (radius * radius))
		return (0);
	if (t)
		*t = t_solution;
	return (1);
}

static int	init_cone_quad(t_cone *cone, t_ray *ray, t_cone_quad *q)
{
	q->oc = vec_sub(ray->origin, cone->apex);
	q->cosine = cos(cone->angle * PI / 180.0);
	q->dv = vec_dot(ray->direction, cone->axis);
	q->xv = vec_dot(q->oc, cone->axis);
	q->a = (q->dv * q->dv) - (q->cosine * q->cosine);
	q->b = 2.0 * ((q->dv * q->xv)
			- (vec_dot(ray->direction, q->oc) * (q->cosine * q->cosine)));
	q->c = (q->xv * q->xv) - (vec_dot(q->oc, q->oc) * (q->cosine * q->cosine));
	if (fabs(q->a) < EPSILON)
		return (0);
	q->discriminant = q->b * q->b - 4.0 * q->a * q->c;
	return (q->discriminant >= 0);
}

static int	cone_root(t_cone_quad *q, double *root)
{
	*root = (-q->b - sqrt(q->discriminant)) / (2.0 * q->a);
	if (*root < EPSILON)
	{
		*root = (-q->b + sqrt(q->discriminant)) / (2.0 * q->a);
		if (*root < EPSILON)
			return (0);
	}
	return (1);
}

static int	cone_height_ok(t_cone *cone, t_ray *ray, double root)
{
	t_vec	hit_point;
	double	s;

	hit_point = vec_add(ray->origin, vec_mult(ray->direction, root));
	s = vec_dot(vec_sub(hit_point, cone->apex), cone->axis);
	return (s > EPSILON && s < cone->height - EPSILON);
}

int	intersect_cone(t_cone *cone, t_ray *ray, double *t)
{
	t_cone_quad	q;
	double		root;

	*t = INFINITY;
	intersect_disk(cone, ray, t);
	if (!init_cone_quad(cone, ray, &q))
		return (*t > EPSILON && *t < INFINITY);
	if (!cone_root(&q, &root))
		return (*t > EPSILON && *t < INFINITY);
	if (!cone_height_ok(cone, ray, root))
		return (*t > EPSILON && *t < INFINITY);
	if (*t > root)
		*t = root;
	return (*t > EPSILON && *t < INFINITY);
}
