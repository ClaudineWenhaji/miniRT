/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:47:15 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/02 15:45:52 by clwenhaj         ###   ########.fr       */
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

static void	update_cylinder_hit(t_cylinder *cylinder, t_ray *ray,
		double root, double *t)
{
	double	s;

	if (root <= EPSILON)
		return ;
	s = vec_dot(vec_sub(vec_add(ray->origin,
					vec_mult(ray->direction, root)),
				cylinder->center), cylinder->axis);
	if (s < cylinder->height / 2.0 && s > -cylinder->height / 2.0)
		if (root < *t)
			*t = root;
}

static int	init_cylinder_quad(t_cylinder *cylinder, t_ray *ray, t_cyl_quad *q)
{
	q->dir_tho = vec_sub(ray->direction, vec_mult(cylinder->axis,
				vec_dot(ray->direction, cylinder->axis)));
	q->d = vec_sub(ray->origin, cylinder->center);
	q->d_tho = vec_sub(q->d, vec_mult(cylinder->axis,
				vec_dot(q->d, cylinder->axis)));
	q->discriminant = ft_discriminant(vec_dot(q->dir_tho, q->dir_tho),
			2 * vec_dot(q->d_tho, q->dir_tho), vec_dot(q->d_tho, q->d_tho)
			- cylinder->radius * cylinder->radius);
	return (vec_dot(q->dir_tho, q->dir_tho) >= EPSILON
		&& q->discriminant >= 0);
}

int	intersect_cylinder(t_cylinder *cy, t_ray *ray, double *t)
{
	t_cyl_quad	q;
	double		root;

	*t = INFINITY;
	root = INFINITY;
	intercept_disk_inf(cy, ray, t);
	if (intercept_disk_sup(cy, ray, &root) && root < *t)
		*t = root;
	if (!init_cylinder_quad(cy, ray, &q))
		return (*t > EPSILON && *t < INFINITY);
	root = (-2 * vec_dot(q.d_tho, q.dir_tho)
			- sqrt(q.discriminant))
		/ (2.0 * vec_dot(q.dir_tho, q.dir_tho));
	update_cylinder_hit(cy, ray, root, t);
	root = (-2 * vec_dot(q.d_tho, q.dir_tho)
			+ sqrt(q.discriminant))
		/ (2.0 * vec_dot(q.dir_tho, q.dir_tho));
	update_cylinder_hit(cy, ray, root, t);
	return (*t > EPSILON && *t < INFINITY);
}
