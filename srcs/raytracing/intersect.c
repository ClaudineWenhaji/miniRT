/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:47:15 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/21 13:15:35 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int intersect_sphere(t_sphere *sphere, t_ray *ray, double *t)
{
    t_vec   oc;
    double  a;
    double  b;
    double  c;
    double  discriminant;
    double  root;

    oc = vec_sub(ray->origin, sphere->center);
    a = vec_dot(ray->direction, ray->direction);
    b = 2.0 * vec_dot(oc, ray->direction);
    c = vec_dot(oc, oc) - (sphere->radius * sphere->radius);
    if (fabs(a) < EPSILON)
        return (0);
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (0);
    root = (-b - sqrt(discriminant)) / (2.0 * a);
    if (root < EPSILON)
    {
        root = (-b + sqrt(discriminant)) / (2.0 * a);
        if (root < EPSILON)
            return (0);
    }
    if (t)
        *t = root;
    return (1);
}

int intersect_plane(t_plane *plane, t_ray *ray, double *t)
{
    double  denominator;
    t_vec   diff;
    
    denominator = vec_dot(plane->normal, ray->direction);
    if (fabs(denominator) < EPSILON)
        return (0);
    diff = vec_sub(plane->point, ray->origin);
    *t = vec_dot(diff, plane->normal) / denominator;
    if (*t < EPSILON)
            return (0);
    return (1);
}

/*static int cone_height_check(t_cone cone, t_vec point)
{
    t_vec   v;
    double  h;
    
    v = vec_sub(point, cone.apex);
    h = vec_dot(v, cone.axis);
    if (h < 0.0)
        return (0);
    if (h > cone.height)
        return (0);
    return (1);
}*/

int intersect_cone(t_cone *cone, t_ray *ray, double *t)
{
    t_vec   oc;
    double  a;
    double  b;
    double  c;
    double  discriminant;
    double  root;
    double  cosine;
    double  dv;
    double  xv;
     
    oc = vec_sub(ray->origin, cone->apex);
    cosine = cos(cone->angle);
    dv = vec_dot(ray->direction, cone->axis);
    xv = vec_dot(oc, cone->axis);
    
    a = (dv * dv) - (cosine * cosine);
    b = 2.0 * ((dv * xv)
        - (vec_dot(ray->direction, oc) * (cosine * cosine)));
    c = (xv * xv) - (vec_dot(oc, oc) * (cosine * cosine));
    if (fabs(a) < EPSILON)
        return (0);
    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0)
        return (0);
    root = (-b - sqrt(discriminant)) / (2.0 * a);
    if (root < EPSILON)
    {
        root = (-b + sqrt(discriminant)) / (2.0 * a);
        if (root < EPSILON)
            return (0);
    }
    //cone avec une hauteur definie
    /*t_vec   point = hit_point(ray, root);  
    if (cone_height_check(cone, point))
        return (0);
    *t = root;*/
    if (t)
        *t = root;
    return (1);
}

int intersect_object(void *object, t_ray *ray, double *t)
{
    if (*(t_type *)object == SPHERE)
        return (intersect_sphere((t_sphere *)object, ray, t));
    if (*(t_type *)object == PLANE)
        return (intersect_plane((t_plane *)object, ray, t));
    if (*(t_type *)object == CONE)
        return (intersect_cone((t_cone *)object, ray, t));
    return (0);
}
