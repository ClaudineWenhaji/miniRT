/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:50:26 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/02 15:50:29 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_discriminant(double a, double b, double c)
{
	return (b * b - 4 * a * c);
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
