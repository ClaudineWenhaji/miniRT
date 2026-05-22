/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:35:02 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/22 12:58:00 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int ft_clamp(int value, int min, int max)
{
    if (value < min)
        return (min);
    if (value > max)
        return (max);
    return (value);
}

int color_to_int(t_color color)
{
    int r;
    int g;
    int b;

    r = ft_clamp((int)color.red, 0, 255);
    g = ft_clamp((int)color.green, 0, 255);
    b = ft_clamp((int)color.blue, 0, 255);
    return ((r << 16) | (g << 8) | b);
}

int hit_scene (t_scene *scene, t_ray *ray, t_hit *closest_t)
{
    t_list  *tmp;
    t_hit   current;
    int     hit_object;

    hit_object = 0;
    closest_t->t = INFINITY;

    tmp = scene->objects;

    while (tmp)
    {
        if (intersect_object(tmp->content, &ray, &current))
        {
            if (current.t < closest_t->t)
            {
                *closest_t = current;
                hit_object = 1;
            }
        }
        tmp = tmp->next;
    }
    return (hit_object);
}

t_color     ray_color(t_scene *scene, t_ray ray, int depth)
{
    t_hit   hit;
    t_color final_color;
    t_color reflected_color;
    t_ray   reflected_ray;
    t_vec   reflected_dir;
    t_vec   light_dir;
    t_list  *light_node;
    double  intensity;
    double  diffuse;
    double  a;
    t_color sky;

    if (depth <= 0)
        return ((t_color){0, 0, 0});
    if (!hit_scene(scene, &ray, &hit))
    {
        a = 0.5 * (ray.direction.y + 1.0);
        sky.red = ((1.0 - a) * 1.0 + a * 0.5) * 255.0;
        sky.green = ((1.0 - a) * 1.0 + a * 0.7) * 255.0;
        sky.blue = ((1.0 - a) * 1.0 + a * 1.0) * 255.0;
        return (sky);
    }
    intensity = 0.0;
    light_node = scene->lights;
    while (light_node)
    {
        t_type_light type = *(t_type_light *)light_node->content;
        if (type == AMBIENT)
            intensity += ((t_ambient *)light_node->content)->ratio;
        else if (type == LIGHT)
        {
            t_light *l = (t_light *)light_node->content;
            light_dir = vec_normalize(vec_sub(l->pos, hit.point));
            double diffuse = vec_dot(hit.normal, light_dir);
            if (diffuse > 0)
                intensity += diffuse * l->brightness;
        }
        light_node = light_node->next;
    }
    if (intensity > 1.0)
        intensity = 1.0;
    final_color.red =   hit.material->color.red *   intensity;
    final_color.green = hit.material->color.green * intensity;
    final_color.blue =  hit.material->color.blue *  intensity;

    if (hit.material->reflectivity > 0.0)
    {
        reflected_dir = vec_reflection(ray.direction, hit.normal);
        reflected_ray.origin = vec_add(hit.point, vec_mult(hit.normal, EPSILON));
        reflected_ray.direction = vec_normalize(reflected_dir);
        
        reflected_color = ray_color(scene, reflected_ray, depth - 1);

        final_color.red =   final_color.red *   (1.0 - hit.material->reflectivity) + reflected_color.red *   hit.material->reflectivity;
        final_color.green = final_color.green * (1.0 - hit.material->reflectivity) + reflected_color.green * hit.material->reflectivity;
        final_color.blue =  final_color.blue *  (1.0 - hit.material->reflectivity) + reflected_color.blue *  hit.material->reflectivity;
    }
    return (final_color);
}


/*static t_vec	get_normal(void *obj, t_vec hit_point, t_color *obj_color)
{
	t_vec	normal;

	if (*(t_type *)obj == SPHERE)
	{
		normal = vec_normalize(
				vec_sub(hit_point, ((t_sphere *)obj)->center));
       
		*obj_color = ((t_sphere *)obj)->color;
	}
	else if (*(t_type *)obj == PLANE)
	{
		normal = vec_normalize(((t_plane *)obj)->normal);
		*obj_color = ((t_plane *)obj)->color;
	}
    else if (*(t_type *)obj == CONE)
    {
        t_vec  pc = vec_sub(hit_point, ((t_cone *)obj)->apex);
        double m = vec_dot(pc, ((t_cone *)obj)->axis);
        double  correction = 1.0 + (tan(((t_cone *)obj)->angle * PI / 180.0)
            * (tan(((t_cone *)obj)->angle * PI / 180.0)));
        
        normal = vec_normalize(
                    vec_sub(pc , vec_mult(((t_cone *)obj)->axis, m * correction)));
        *obj_color = ((t_cone *)obj)->color;
    }
	else
		normal = vector(0, 1, 0); // Default safe value
	return (normal);
}*/

/*int ray_color(t_scene *scene, void *obj, t_ray ray, double t)
{
    t_vec   hit_point;
    t_vec   normal;
    t_vec   light_dir;
    double  intensity;
    t_color final_color;
    t_color obj_color;
    t_list  *light_node;
    double  a;
    t_color sky;
    //t_ray   reflected_ray;
    //t_vec   reflected_dir;

    if (!obj)
    {
        a = 0.5 * (ray.direction.y + 1.0);
        sky.red = ((1.0 - a) * 1.0 + a * 0.5) * 255.0;
        sky.green = ((1.0 - a) * 1.0 + a * 0.7) * 255.0;
        sky.blue = ((1.0 - a) * 1.0 + a * 1.0) * 255.0;
        return (color_to_int(sky));
    }
    intensity = 0.0;
    hit_point = vec_add(ray.origin, vec_mult(ray.direction, t));
    normal = get_normal(obj, hit_point, &obj_color);
    if (vec_dot(normal, ray.direction) > 0)
			normal = vec_mult(normal, -1);
    
    //reflected_dir = vec_reflection(ray.direction, normal);
    //reflected_ray.origin = vec_add(hit_point, vec_mult(normal, EPSILON));
    //reflected_ray.direction = vec_normalize(reflected_dir);
    
    light_node = scene->lights;
    while (light_node)
    {
        t_type_light type = *(t_type_light *)light_node->content;
        if (type == AMBIENT)
            intensity += ((t_ambient *)light_node->content)->ratio;
        else if (type == LIGHT)
        {
            t_light *l = (t_light *)light_node->content;
            light_dir = vec_normalize(vec_sub(l->pos, hit_point));
            //light_dir = vec_normalize(vec_sub(l->pos, reflected_ray.origin));
            double diffuse = vec_dot(normal, light_dir);
            //double diffuse = vec_dot(reflected_ray.direction, light_dir);
            if (diffuse > 0)
                intensity += diffuse * l->brightness;
        }
        light_node = light_node->next;
    }
    if (intensity > 1.0)
        intensity = 1.0;
    final_color.red = obj_color.red * intensity;
    final_color.green = obj_color.green * intensity;
    final_color.blue = obj_color.blue * intensity;
    return (color_to_int(final_color));
}*/
