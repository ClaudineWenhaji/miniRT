/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 18:07:33 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/01 18:08:21 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	vec_div(t_vec v, double k)
{
	if (fabs(k) < EPSILON)
		return ((t_vec){0, 0, 0});
	v.x = v.x / k;
	v.y = v.y / k;
	v.z = v.z / k;
	return (v);
}

t_vec	vec_reflection(t_vec dir, t_vec normal)
{
	t_vec	result;

	result = vec_mult(normal, 2.0 * vec_dot(dir, normal));
	result = vec_sub(dir, result);
	return (result);
}
