/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard_pattern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:47:07 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/01 18:29:50 by clwenhaj         ###   ########.fr       */
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
	t_vec	u;
	t_vec	v;
	int		x_check;
	int		y_check;
	double	u_coord;
	double	v_coord;
	t_vec	local_hit;

	local_hit = vec_sub(hit_point, plane->point);
	get_plane_axis(plane->normal, &u, &v);
	u_coord = vec_dot(local_hit, u);
	v_coord = vec_dot(local_hit, v);
	x_check = (int)floor(u_coord * material->checker_scale);
	y_check = (int)floor(v_coord * material->checker_scale);
	if (((x_check + y_check) % 2 + 2) % 2 == 0)
		return (material->checker_color1);
	return (material->checker_color2);
}

t_color	checker_sphere(t_sphere *sphere,
		t_material *material, t_point hit_point)
{
	t_vec	local_hit;
	int		x_check;
	int		y_check;
	double	phi;
	double	theta;
	double	u_coord;
	double	v_coord;

	local_hit = vec_normalize(vec_sub(hit_point, sphere->center));
	phi = atan2(local_hit.z, local_hit.x);
	theta = acos(local_hit.y);
	u_coord = 0.5 + phi / (2 * PI);
	v_coord = theta / PI;
	x_check = (int)floor(u_coord * material->checker_scale);
	y_check = (int)floor(v_coord * material->checker_scale);
	if (((x_check + y_check) % 2 + 2) % 2 == 0)
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
	t_vec	local;
	t_vec	tangent;
	t_vec	bitangent;
	double	x;
	double	y;
	double	u;
	double	v;
	int		cell_x;
	int		cell_y;

	local = vec_sub(hit_point, cylinder->center);
	cylinder_basis(cylinder->axis, &tangent, &bitangent);
	x = vec_dot(local, tangent);
	y = vec_dot(local, bitangent);
	u = atan2(y, x);
	u = (u + PI) / (2.0 * PI);
	if (u >= 1.0)
		u = 0.0;
	v = vec_dot(local, cylinder->axis) / cylinder->height;
	cell_x = (int)floor(u * material->checker_scale);
	cell_y = (int)floor(v * material->checker_scale);
	if (((cell_x + cell_y) % 2 + 2) % 2 == 0)
		return (material->checker_color1);
	return (material->checker_color2);
}

static t_color	checker_disk(t_cone *cone, t_material *material,
		t_point hit_point, t_vec tangent, t_vec bitangent)
{
	t_vec	center;
	t_vec	local;
	int		cell_x;
	int		cell_y;

	center = vec_add(cone->apex, vec_mult(cone->axis, cone->height));
	local = vec_sub(hit_point, center);
	cell_x = (int)floor(vec_dot(local, tangent) * material->checker_scale);
	cell_y = (int)floor(vec_dot(local, bitangent) * material->checker_scale);
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
	t_vec	local;
	t_vec	tangent;
	t_vec	bitangent;
	double	x;
	double	y;
	double	angle;
	double	u;
	double	v;
	int		cell_u;
	int		cell_v;

	local = vec_sub(hit_point, cone->apex);
	cone_basis(cone->axis, &tangent, &bitangent);
	x = vec_dot(local, tangent);
	y = vec_dot(local, bitangent);
	angle = atan2(y, x);
	u = (angle + PI) / (2.0 * PI);
	if (u >= 1.0)
		u = 0.0;
	v = vec_dot(local, cone->axis) / cone->height;
	if (v <= EPSILON)
		return (material->checker_color1);
	if (v >= 1.0 - EPSILON)
		return (checker_disk(cone, material, hit_point, tangent, bitangent));
	cell_u = (int)floor(u * material->checker_scale);
	cell_v = (int)floor(v * material->checker_scale);
	if (((cell_u + cell_v) % 2 + 2) % 2 == 0)
		return (material->checker_color2);
	return (material->checker_color1);
}
