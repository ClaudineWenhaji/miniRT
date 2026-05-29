/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:12:51 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/29 15:04:09 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	get_normal_cone(t_cone *cone, t_point hit_point)
{
	t_vec	normal;
	t_vec	pc;
	double	m;
	double	correction;
	double	s;

	s = vec_dot(vec_sub(hit_point, cone->apex), cone->axis);
	if (s > cone->height - EPSILON)
		return (cone->axis);
	pc = vec_sub(hit_point, cone->apex);
	m = vec_dot(pc, cone->axis);
	correction = 1.0 + tan(cone->angle * PI / 180.0)
		* tan(cone->angle * PI / 180.0);
	normal = vec_normalize(
			vec_sub(pc, vec_mult(cone->axis, m * correction)));
	return (normal);
}

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

int	intersect_cone(t_cone *cone, t_ray *ray, double *t)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;
	double	cosine;
	double	dv;
	double	xv;
	t_vec	hit_point;
	double	s;

	*t = INFINITY;
	intersect_disk(cone, ray, t);
	oc = vec_sub(ray->origin, cone->apex);
	cosine = cos(cone->angle * PI / 180.0);
	dv = vec_dot(ray->direction, cone->axis);
	xv = vec_dot(oc, cone->axis);
	a = (dv * dv) - (cosine * cosine);
	b = 2.0 * ((dv * xv)
			- (vec_dot(ray->direction, oc) * (cosine * cosine)));
	c = (xv * xv) - (vec_dot(oc, oc) * (cosine * cosine));
	//if (fabs(a) < EPSILON)
	//	return (*t > EPSILON && *t < INFINITY);
	if (fabs(a) < EPSILON)
		return (0);
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (*t > EPSILON && *t < INFINITY);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root < EPSILON)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root < EPSILON)
			return (*t > EPSILON && *t < INFINITY);
	}
	hit_point = vec_add(ray->origin, vec_mult(ray->direction, root));
	s = vec_dot(vec_sub(hit_point, cone->apex), cone->axis);
	if (s < EPSILON)
		return (*t > EPSILON && *t < INFINITY);
	if (s > (cone->height) - EPSILON)
		return (*t > EPSILON && *t < INFINITY);
	if (*t > root)
		*t = root;
	return (*t > EPSILON && *t < INFINITY);
}
