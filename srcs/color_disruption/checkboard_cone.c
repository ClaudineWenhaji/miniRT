/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:34:15 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/08 14:47:57 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	checker_disk(t_cone *cone, t_material *material,
		t_point hit_point, t_cone_uv uv)
{
	t_vec	center;
	t_vec	local;
	int		cell_x;
	int		cell_y;

	center = vec_add(cone->apex, vec_mult(cone->axis, cone->height));
	local = vec_sub(hit_point, center);
	cell_x = (int)floor(vec_dot(local, uv.tangent) * material->checker_scale);
	cell_y = (int)floor(vec_dot(local, uv.bitangent) * material->checker_scale);
	if (((cell_x + cell_y) % 2 + 2) % 2 == 0)
		return (material->checker_color1);
	return (material->checker_color2);
}

static void	cone_basis(t_vec axis, t_vec *t, t_vec *b)
{
	t_vec	ref;

	if (fabs(axis.y) < 0.999)
		ref = vector(0, 1, 0);
	else
		ref = vector(0, 0, 1);
	*t = vec_normalize(vec_cross_prod(ref, axis));
	*b = vec_cross_prod(axis, *t);
}

t_color	checker_cone(t_cone *cone, t_material *material,
		t_point hit_point)
{
	t_vec		local;
	t_cone_uv	uv;

	local = vec_sub(hit_point, cone->apex);
	cone_basis(cone->axis, &uv.tangent, &uv.bitangent);
	uv.angle = atan2(vec_dot(local, uv.bitangent), vec_dot(local, uv.tangent));
	uv.u_coord = (uv.angle + PI) / (2.0 * PI);
	if (uv.u_coord >= 1.0)
		uv.u_coord = 0.0;
	uv.v_coord = vec_dot(local, cone->axis) / cone->height;
	if (uv.v_coord <= EPSILON)
		return (material->checker_color1);
	if (uv.v_coord >= 1.0 - EPSILON)
		return (checker_disk(cone, material, hit_point, uv));
	uv.x_check = (int)floor(uv.u_coord * material->checker_scale);
	uv.y_check = (int)floor(uv.v_coord * material->checker_scale);
	if (((uv.x_check + uv.y_check) % 2 + 2) % 2 == 0)
		return (material->checker_color2);
	return (material->checker_color1);
}
