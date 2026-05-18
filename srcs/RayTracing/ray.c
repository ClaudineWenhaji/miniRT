/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:48:21 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/13 13:18:57 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    ray_variables(t_ray *ray, t_point *ori, t_vec *dir)
{
    ray->origin.x = ori->x;
    ray->origin.y = ori->y;
    ray->origin.z = ori->z;
    ray->direction.x = dir->x;
    ray->direction.y = dir->y;
    ray->direction.z = dir->z;
    ray->direction =vec_normalize(ray->direction);
}

t_vec   *ray_equation(t_vec *ray_coord, t_ray *ray, double t)
{
    ray_coord->x = ray->origin.x + (t * ray->direction.x);
    ray_coord->y = ray->origin.y + (t * ray->direction.y);
    ray_coord->z = ray->origin.z + (t * ray->direction.z);
    return (ray_coord);
}

t_color  trace_ray(t_data *data, t_ray ray)
{
    t_object    *object;
    double      closest_t;
    double      t;
    t_color     pixel_color;

    pixel_color = (t_color){0, 0, 0};
    closest_t = INFINITY;
    object = data->scene->objects;
    while (object)
    {
        if (object->intersect(object->data, ray, &t))
        {
                if (t < closest_t)
                {
                    closest_t = t;
                    pixel_color = object->color;
                }
        }
        object = object->next;
    }
    return (pixel_color);
}