/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 09:43:43 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/18 16:47:38 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int intersect_sphere(void *data, t_ray ray, double *t)
{
    t_sphere *sphere;
    double  discriminant;
    double  a;
    double  b;
    double  c;
    double  t1;
    double  t2;
    t_vec   oc;

    sphere = (t_sphere *)data;
    oc = vec_sub(ray.origin, sphere->center);
    a = vec_dot(ray.direction, ray.direction);
    b = 2.0 * vec_dot(oc, ray.direction);
    c = vec_dot(oc, oc)
        - sphere->radius * sphere->radius;
    discriminant = b * b - 4.0 * (a * c);
    if (discriminant < 0.0)
        return (0);
    t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    if (t1 > EPSILON)
        *t = t1;
    else if (t2 > EPSILON)
        *t = t2;
    else
        return (0);
    return (1);
}

