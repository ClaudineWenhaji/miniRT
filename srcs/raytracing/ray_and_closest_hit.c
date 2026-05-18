/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_and_closest_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:48:21 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/18 18:29:29 by clwenhaj         ###   ########.fr       */
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
    t_list      *current;
    t_object    *object;
    t_sphere    *sphere;
    t_light     *light;
    t_point     hit_point;
    t_vec       normal;
    t_vec       light_dir;
    double      intensity;
    double      closest_t;
    double      t;
    t_color     pixel_color;

    pixel_color = (t_color){0, 0, 0};
    closest_t = INFINITY;
    light = NULL;
    object = NULL;
    light = (t_light *)data->scene->lights->content;
    current = data->scene->objects;
    while (current)
    {
        object = (t_object *)current->content;
        if (intersect_object(object, ray, &t))
        {
                if (t < closest_t)
                {
                    closest_t = t;
                    sphere = (t_sphere *)object->data;
                    hit_point = vec_add(ray.origin, vec_mult(ray.direction, t));
                    normal = vec_normalize(vec_sub(hit_point, sphere->center));
                    light_dir = vec_normalize(vec_sub(light->pos, hit_point));
                    intensity = vec_dot(normal, light_dir);
                    if (intensity < 0)
                        intensity = 0;
                    pixel_color.red = sphere->color.red * intensity;
                    pixel_color.green = sphere->color.green * intensity;
                    pixel_color.blue = sphere->color.blue * intensity;
                    //pixel_color = object->color;
                }
        }
        current = current->next;
    }
    return (pixel_color);
}
