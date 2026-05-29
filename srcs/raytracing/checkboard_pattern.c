/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard_pattern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:47:07 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/29 16:37:18 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


static void get_plane_axis(t_vec normal, t_vec *u, t_vec *v)
{
    t_vec temp;
    if (fabs(normal.x) > fabs(normal.y))
        temp = (t_vec){0, 1, 0};
    else
        temp = (t_vec){1, 0, 0};
    *u = vec_normalize(vec_cross_prod(temp, normal));
    *v = vec_normalize(vec_cross_prod(normal, *u));
}   

t_color checker_plane(t_plane *plane, t_material *material, t_point hit_point)
{
    t_vec u, v;
    t_vec local_hit = vec_sub(hit_point, plane->point);
    get_plane_axis(plane->normal, &u, &v);
    double u_coord = vec_dot(local_hit, u);
    double v_coord = vec_dot(local_hit, v);
    int x_check = (int)floor(u_coord * material->checker_scale);
    int y_check = (int)floor(v_coord * material->checker_scale);   
    if (((x_check + y_check) % 2 + 2) % 2 == 0)
        return (material->checker_color1);
    return (material->checker_color2);     
}

t_color checker_sphere(t_sphere *sphere, t_material *material, t_point hit_point)
{
    t_vec local_hit = vec_normalize(vec_sub(hit_point, sphere->center));
    
    double phi = atan2(local_hit.z, local_hit.x);
    double theta = acos(local_hit.y);
    
    double u_coord = 0.5 + phi / (2 * PI);
    double v_coord = theta / PI;
    
    int x_check = (int)floor(u_coord * material->checker_scale);
    int y_check = (int)floor(v_coord * material->checker_scale);
    if (((x_check + y_check) % 2 + 2) % 2 == 0)
        return (material->checker_color1);
    return (material->checker_color2);
}

t_color checker_cylinder(t_cylinder *cylinder, t_material *material, t_point hit_point)
{
    t_vec local_hit = vec_sub(hit_point, cylinder->center);
    
    double phi = atan2(local_hit.z, local_hit.x);
    double u_coord = (phi + PI) / (2.0 * PI);
    double v_coord = local_hit.y / cylinder->height;
    
    int x_check = (int)floor(u_coord * material->checker_scale);
    int y_check = (int)floor(v_coord * material->checker_scale);
  
    if (((x_check + y_check) % 2 + 2) % 2 == 0)
        return (material->checker_color1);
    return (material->checker_color2);     
}

/*t_color checker_cone(t_cone *cone, t_material *material, t_point hit_point)
{
    t_vec local_hit = vec_sub(hit_point, cone->apex);
    
    double phi = atan2(local_hit.z, local_hit.x);
    double u_coord = (phi + PI) / (2.0 * PI);
    //double v_coord = local_hit.y / cone->height;
    double v_coord = vec_dot(local_hit, cone->axis) / cone->height; // Use distance from apex for v coordinate
    
    int x_check = (int)floor(u_coord * material->checker_scale);
    int y_check = (int)floor(v_coord * material->checker_scale);
    if (((x_check + y_check) % 2 + 2) % 2 == 0)
        return (material->checker_color1);
    return (material->checker_color2);     
}*/

/*t_color	checker_disk(t_cone *cone, t_material *material, t_point hit_point)
{
	t_vec	center;
	t_vec	local;
	int		x;
	int		y;

	center = vec_add(cone->apex,
			vec_mult(cone->axis, cone->height));

	local = vec_sub(hit_point, center);

	x = (int)floor(local.x * material->checker_scale * 0.1);
	y = (int)floor(local.z * material->checker_scale * 0.1);

	if (((x + y) % 2 + 2) % 2 == 0)
		return (material->checker_color1);

	return (material->checker_color2);
}*/

t_color	checker_disk(t_cone *cone,
	t_material *material,
	t_point hit_point)
{
	t_vec	center;
	t_vec	local;
	t_vec	ref;
	t_vec	tangent;
	t_vec	bitangent;
	double	u;
	double	v;
	int		x;
	int		y;

	center = vec_add(cone->apex,
			vec_mult(cone->axis, cone->height));

	local = vec_sub(hit_point, center);

	/*
	** base locale du disque
	*/

	if (fabs(cone->axis.y) < 0.999)
		ref = vector(0, 1, 0);
	else
		ref = vector(1, 0, 0);

	tangent = vec_normalize(vec_cross_prod(ref, cone->axis));
	bitangent = vec_cross_prod(cone->axis, tangent);

	/*
	** projection locale
	*/

	u = vec_dot(local, tangent);
	v = vec_dot(local, bitangent);

	x = (int)floor(u * material->checker_scale);
	y = (int)floor(v * material->checker_scale);

	if ((x + y) % 2 == 0)
		return (material->checker_color1);

	return (material->checker_color2);
}

t_color	    checker_cone(t_cone *cone, t_material *material, t_point hit_point)
{
	t_vec	local_hit;
	t_vec	tangent;
	t_vec	bitangent;
	t_vec	ref;
	double	x;
	double	y;
	double	phi;
	double	u;
	double	v;
	int		check_x;
	int		check_y;

	local_hit = vec_sub(hit_point, cone->apex);

	/*
	** Construction d'une base locale orthogonale
	** autour de cone->axis
	*/

	if (fabs(cone->axis.y) < 0.999)
		ref = vector(0, 1, 0);
	else
		ref = vector(1, 0, 0);

	tangent = vec_normalize(vec_cross_prod(ref, cone->axis));
	bitangent = vec_cross_prod(cone->axis, tangent);

	/*
	** Projection locale
	*/

	x = vec_dot(local_hit, tangent);
	y = vec_dot(local_hit, bitangent);

	/*
	** Coordonnée angulaire
	*/

	phi = atan2(y, x);

	u = (phi + PI) / (2.0 * PI);

	/* Coordonnée hauteur*/


	v = vec_dot(local_hit, cone->axis) / cone->height;

	/*
	** Protection apex
	*/
    if (v < EPSILON)
    {
        return (material->checker_color1);  
    }
 
	if (v > 1.0 - EPSILON)
	{
        return (checker_disk(cone, material, hit_point));
	}

	check_x = (int)floor(u * material->checker_scale);
	check_y = (int)floor(v * material->checker_scale);

	if (((check_x + check_y) % 2 + 2) % 2 == 0)
		return (material->checker_color1);

	return (material->checker_color2);
}