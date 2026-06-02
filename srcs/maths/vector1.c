/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:06:09 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/01 18:08:11 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec_dot(t_vec u, t_vec v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_vec	vec_cross_prod(t_vec u, t_vec v)
{
	t_vec	result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	return (result);
}

t_vec	vec_normalize(t_vec v)
{
	double	norm;

	norm = vec_length(v);
	if (fabs(norm) < EPSILON)
		return ((t_vec){0, 0, 0});
	norm = 1.0 / norm;
	v.x = v.x * norm;
	v.y = v.y * norm;
	v.z = v.z * norm;
	return (v);
}

double	distance(t_vec a, t_vec b)
{
	return (vec_length(vec_sub(b, a)));
}

t_vec	vec_inv(t_vec v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}
