/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard_pattern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:47:07 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/28 14:47:35 by clwenhaj         ###   ########.fr       */
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
    int x_check = (int)floor(u_coord / material->checker_scale);
    int y_check = (int)floor(v_coord / material->checker_scale);   
    if (((x_check + y_check) % 2 + 2) % 2 == 0)
        return (material->checker_color1);
    return (material->checker_color2);     
}

t_color checker_sphere(t_sphere *sphere, t_material *material, t_point hit_point)
{
    double phi = atan2(hit_point.z - sphere->center.z, hit_point.x - sphere->center.x);
    double theta = acos((hit_point.y - sphere->center.y) / sphere->radius);
    double u_coord = 0.5 + phi / (2 * PI);
    double v_coord = 0.5 - theta / PI;
    int x_check = (int)floor(u_coord / material->checker_scale);
    int y_check = (int)floor(v_coord / material->checker_scale);
    if (((x_check + y_check) % 2 + 2) % 2 == 0)
        return (material->checker_color1);
    return (material->checker_color2);
}

t_color checker_cylinder(t_cylinder *cylinder, t_material *material, t_point hit_point)
{
    t_vec local_hit = vec_sub(hit_point, cylinder->center);
    int x_check = (int)floor(local_hit.x / material->checker_scale);
    int y_check = (int)floor(local_hit.y / material->checker_scale);
    int z_check = (int)floor(local_hit.z / material->checker_scale);
    if (((x_check + y_check + z_check) % 2 + 2) % 2 == 0)
        return (material->checker_color1);
    return (material->checker_color2);     
}

t_color checker_cone(t_cone *cone, t_material *material, t_point hit_point)
{
    t_vec local_hit = vec_sub(hit_point, cone->apex);
    int x_check = (int)floor(local_hit.x / material->checker_scale);
    int y_check = (int)floor(local_hit.y / material->checker_scale);
    int z_check = (int)floor(local_hit.z / material->checker_scale);
    if (((x_check + y_check + z_check) % 2 + 2) % 2 == 0)
        return (material->checker_color1);
    return (material->checker_color2);     
}