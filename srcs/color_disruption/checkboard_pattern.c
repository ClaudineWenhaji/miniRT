/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard_pattern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:47:07 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/03 14:34:06 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	get_plane_axis(t_vec normal, t_vec *u, t_vec *v)
{
	t_vec	temp;

	if (fabs(normal.x) > fabs(normal.y))
		temp = (t_vec){0, 1, 0};
	else
		temp = (t_vec){1, 0, 0};
	*u = vec_normalize(vec_cross_prod(temp, normal));
	*v = vec_normalize(vec_cross_prod(normal, *u));
}

t_color	checker_plane(t_plane *plane, t_material *material, t_point hit_point)
{
	t_vec		u;
	t_vec		v;
	t_plane_uv	uv;
	t_vec		local_hit;

	local_hit = vec_sub(hit_point, plane->point);
	get_plane_axis(plane->normal, &u, &v);
	uv.u_coord = vec_dot(local_hit, u);
	uv.v_coord = vec_dot(local_hit, v);
	uv.x_check = (int)floor(uv.u_coord * material->checker_scale);
	uv.y_check = (int)floor(uv.v_coord * material->checker_scale);
	if (((uv.x_check + uv.y_check) % 2 + 2) % 2 == 0)
		return (material->checker_color1);
	return (material->checker_color2);
}

t_color	checker_sphere(t_sphere *sphere,
		t_material *material, t_point hit_point)
{
	t_vec			local_hit;
	t_sph_uv		uv;
	double			phi;
	double			theta;

	local_hit = vec_normalize(vec_sub(hit_point, sphere->center));
	phi = atan2(local_hit.z, local_hit.x);
	theta = acos(local_hit.y);
	uv.u_coord = 0.5 + phi / (2 * PI);
	uv.v_coord = theta / PI;
	uv.x_check = (int)floor(uv.u_coord * material->checker_scale);
	uv.y_check = (int)floor(uv.v_coord * material->checker_scale);
	if (((uv.x_check + uv.y_check) % 2 + 2) % 2 == 0)
		return (material->checker_color1);
	return (material->checker_color2);
}

static void	cylinder_basis(t_vec axis, t_vec *t, t_vec *b)
{
	t_vec	ref;

	if (fabs(axis.y) < 0.999)
		ref = vector(0, 1, 0);
	else
		ref = vector(1, 0, 0);
	*t = vec_normalize(vec_cross_prod(ref, axis));
	*b = vec_cross_prod(axis, *t);
}

t_color	checker_cylinder(t_cylinder *cylinder,
		t_material *material, t_point hit_point)
{
	t_vec		local;
	t_vec		tangent;
	t_vec		bitangent;
	t_cyl_uv	uv;

	local = vec_sub(hit_point, cylinder->center);
	cylinder_basis(cylinder->axis, &tangent, &bitangent);
	uv.u_coord = atan2(vec_dot(local, bitangent), vec_dot(local, tangent));
	uv.u_coord = (uv.u_coord + PI) / (2.0 * PI);
	if (uv.u_coord >= 1.0)
		uv.u_coord = 0.0;
	uv.v_coord = vec_dot(local, cylinder->axis) / cylinder->height;
	uv.x_check = (int)floor(uv.u_coord * material->checker_scale);
	uv.y_check = (int)floor(uv.v_coord * material->checker_scale);
	if (((uv.x_check + uv.y_check) % 2 + 2) % 2 == 0)
		return (material->checker_color1);
	return (material->checker_color2);
}
