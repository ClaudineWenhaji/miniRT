/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:35:02 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/20 14:34:39 by clwenhaj         ###   ########.fr       */
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

static int color_to_int(t_color color)
{
    int r;
    int g;
    int b;

    r = ft_clamp((int)color.red, 0, 255);
    g = ft_clamp((int)color.green, 0, 255);
    b = ft_clamp((int)color.blue, 0, 255);
    return ((r << 16) | (g << 8) | b);
}


int ray_color(t_scene *scene, void *obj, t_ray ray, double t)
{
    t_vec   hit_point;
    t_vec   normal;
    t_vec   light_dir;
    double  intensity;
    t_color final_color;
    t_list  *light_node;
    double  a;
    t_color sky;

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
    if (*(t_type *)obj == SPHERE)
        normal = vec_normalize(vec_sub(hit_point, ((t_sphere *)obj)->center));
    else
        normal = vector(0, 1, 0); // Default safe value
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
            double diffuse = vec_dot(normal, light_dir);
            if (diffuse > 0)
                intensity += diffuse * l->brightness;
        }
        light_node = light_node->next;
    }
    if (intensity > 1.0)
        intensity = 1.0;
    final_color.red = ((t_sphere *)obj)->color.red * intensity;
    final_color.green = ((t_sphere *)obj)->color.green * intensity;
    final_color.blue = ((t_sphere *)obj)->color.blue * intensity;
    return (color_to_int(final_color));
}

// ecrire un pixel de couleur donnee dans une image, a la position x,y
// on manipule les memoires graphiques donc char * pour avancer de 1 octet
// int * permet d'avancer de 4 octets (32 bits)
void put_pixel(t_img *img, int x, int y, int color)
{
    char    *dest;

    dest = img->data
        + (y * img->size_line)
        + (x * (img->bit_per_pixel / 8));
    *(unsigned int *)dest = color;
}
