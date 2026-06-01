/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:47:15 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/01 14:23:16 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	intercept_disk_inf(t_cylinder *cylinder, t_ray *ray, double *t)
{
	t_vec	center_down;
	double	t_sol;
	t_vec	vec_diff;

	center_down = vec_sub(cylinder->center, vec_mult(cylinder->axis,
				cylinder->height / 2.0));
	if (fabs(vec_dot(ray->direction, cylinder->axis)) < EPSILON)
		return (0);
	t_sol = vec_dot(vec_sub(center_down, ray->origin), cylinder->axis)
		/ vec_dot(ray->direction, cylinder->axis);
	if (t_sol < EPSILON)
		return (0);
	vec_diff = vec_sub(vec_add(ray->origin, vec_mult(ray->direction, t_sol)),
			center_down);
	if (vec_dot(vec_diff, vec_diff) > cylinder->radius * cylinder->radius)
		return (0);
	*t = t_sol;
	return (1);
}

static int	intercept_disk_sup(t_cylinder *cylinder, t_ray *ray, double *t)
{
	t_vec	center_up;
	double	t_sol;
	t_vec	vec_diff;

	center_up = vec_add(cylinder->center, vec_mult(cylinder->axis,
				cylinder->height / 2.0));
	if (fabs(vec_dot(ray->direction, cylinder->axis)) < EPSILON)
		return (0);
	t_sol = vec_dot(vec_sub(center_up, ray->origin), cylinder->axis)
		/ vec_dot(ray->direction, cylinder->axis);
	if (t_sol < EPSILON)
		return (0);
	vec_diff = vec_sub(vec_add(ray->origin, vec_mult(ray->direction, t_sol)),
			center_up);
	if (vec_dot(vec_diff, vec_diff) > cylinder->radius * cylinder->radius)
		return (0);
	*t = t_sol;
	return (1);
}

t_vec	get_normal_cylinder(t_cylinder *cylinder, t_point hit_point)
{
	double	s;

	s = vec_dot(vec_sub(hit_point, cylinder->center), cylinder->axis);
	if (s > cylinder->height / 2.0 - EPSILON)
		return (cylinder->axis);
	else if (s < -cylinder->height / 2.0 + EPSILON)
		return (vec_mult(cylinder->axis, -1.0));
	else
		return (vec_normalize(vec_sub(hit_point, vec_add(cylinder->center,
						vec_mult(cylinder->axis, s)))));
}

int	intersect_cylinder(t_cylinder *cylinder, t_ray *ray, double *t)
{
	t_vec	d;
	t_vec	direction_tho;
	t_vec	d_tho;
	double	discriminant;
	double	root;
	double	s;

	*t = INFINITY;
	root = INFINITY;
	intercept_disk_inf(cylinder, ray, t);
	if (intercept_disk_sup(cylinder, ray, &root) && root < *t)
		*t = root;
	direction_tho = vec_sub(ray->direction, vec_mult(cylinder->axis,
				vec_dot(ray->direction, cylinder->axis)));
	d = vec_sub(ray->origin, cylinder->center);
	d_tho = vec_sub(d, vec_mult(cylinder->axis, vec_dot(d, cylinder->axis)));
	discriminant = ft_discriminant(vec_dot(direction_tho, direction_tho),
			2 * vec_dot(d_tho, direction_tho), vec_dot(d_tho, d_tho)
			- cylinder->radius * cylinder->radius);
	if (discriminant < 0 || vec_dot(direction_tho, direction_tho) < EPSILON)
		return (*t > EPSILON && *t < INFINITY);
	root = (-2 * vec_dot(d_tho, direction_tho) - sqrt(discriminant))
		/ (2.0 * vec_dot(direction_tho, direction_tho));
	if (root > EPSILON)
	{
		s = vec_dot(vec_sub(vec_add(ray->origin,
						vec_mult(ray->direction, root)),
					cylinder->center), cylinder->axis);
		if (s < cylinder->height / 2.0 && s > -cylinder->height / 2.0)
			if (root < *t)
				*t = root;
	}
	root = (-2 * vec_dot(d_tho, direction_tho) + sqrt(discriminant))
		/ (2.0 * vec_dot(direction_tho, direction_tho));
	if (root > EPSILON)
	{
		s = vec_dot(vec_sub(vec_add(ray->origin,
						vec_mult(ray->direction, root)),
					cylinder->center), cylinder->axis);
		if (s < cylinder->height / 2.0 && s > -cylinder->height / 2.0)
			if (root < *t)
				*t = root;
	}
	return (*t > EPSILON && *t < INFINITY);
}
