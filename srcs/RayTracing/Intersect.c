/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 09:43:43 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/14 10:23:12 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int intersect_sphere(t_sphere sphere, t_ray ray, double *t)
{
    double  discriminant;
    double  a;
    double  b;
    double  c;
    t_vec   oc;
    double  t1;
    double  t2;

    oc = vec_sub(ray.origin, sphere.center);
    a = vec_dot(ray.direction, ray.direction);
    b = 2 * vec_dot(oc, ray.direction);
    c = vec_dot(oc, oc) - sphere.radius * sphere.radius;
    discriminant = b * b - 4 * (a * c);
    if (discriminant < 0)
        return (0);
    t1 = (-b - sqrt(discriminant)) / 2.0 * a;
    t2 = (-b + sqrt(discriminant)) / 2.0 * a;
    if (t1 > EPSILON)
        *t = t1;
    else if (t2 > EPSILON)
        *t = t2;
    else
        return (0);
    return (1);
}