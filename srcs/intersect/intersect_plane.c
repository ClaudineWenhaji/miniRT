/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:40:50 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/02 15:41:13 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_plane(t_plane *plane, t_ray *ray, double *t)
{
	double	denominator;
	t_vec	diff;

	denominator = vec_dot(plane->normal, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (0);
	diff = vec_sub(plane->point, ray->origin);
	*t = vec_dot(diff, plane->normal) / denominator;
	if (*t < EPSILON)
		return (0);
	return (1);
}
