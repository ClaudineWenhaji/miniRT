/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycolor_algorithm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:19:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/28 14:52:43 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define MAX_DEPTH 5

static  t_color	c_mult(t_color c, double f)
{
	return ((t_color){c.red * f, c.green * f, c.blue * f});
}

static  t_color	c_add(t_color c1, t_color c2)
{
	return ((t_color){c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue});
}

static  t_color c_prod(t_color color_a, t_color color_b)
{
    return ((t_color){color_a.red * color_b.red, color_a.green * color_b.green,
            color_a.blue * color_b.blue});
}

static int color_to_int_local(t_color color)
{
    int r = (int)fmin(255.0, fmax(0.0, color.red * 255.0));
    int g = (int)fmin(255.0, fmax(0.0, color.green * 255.0));
    int b = (int)fmin(255.0, fmax(0.0, color.blue * 255.0));
    return ((r << 16) | (g << 8) | b);
}

static t_color default_color(t_scene *scene)
{
    t_list      *light;
    t_ambient   *amb;

    light = scene->lights;
    while (light)
    {
        if (*(t_type_light *)light->content == AMBIENT)
        {
            amb = (t_ambient *)light->content;
            return (c_mult(amb->color, amb->ratio));
        }
        light = light->next;
    }
    return ((t_color){0.0, 0.0, 0.0});
}

static void *find_closest_point(t_ray *ray, t_list *objects, double *t_out)
{
    double  closest_t = INFINITY;
    double  t;
    t_list  *node = objects;
    void    *closest_object = NULL;

    while (node)
    {
        if (intersect_object(node->content, ray, &t))
        {
            if (t > EPSILON && t < closest_t)
            {
                closest_t = t;
                closest_object = node->content;
            }
        }
        node = node->next;
    }
    *t_out = closest_t;
    return (closest_object);
}

static t_vec get_normal_any(void *obj, t_point hit_point)
{
    t_type type = *(t_type *)obj;
    if (type == SPHERE)
        return (vec_normalize(vec_sub(hit_point, ((t_sphere *)obj)->center)));
    if (type == PLANE)
        return (vec_normalize(((t_plane *)obj)->normal));
    if (type == CYLINDER)
        return (get_normal_cylinder((t_cylinder *)obj, hit_point));
    if (type == CONE)
        return (get_normal_cone((t_cone *)obj, hit_point));
    return (vector(0, 1, 0));
}

static t_material get_obj_material(void *object)
{
    if (*(t_type *)object == SPHERE)
        return (((t_sphere *)object)->material);
    if (*(t_type *)object == CYLINDER)
        return (((t_cylinder *)object)->material);
    if (*(t_type *)object == CONE)
        return (((t_cone *)object)->material);
    if (*(t_type *)object == PLANE)
        return (((t_plane *)object)->material);
    return ((t_material){{0,0,0}, 1, 0, 1, 1, 0, 1, {0,0,0}, {0,0,0}, 0});
}

static t_color get_object_color(void *object, t_point hit_point)
{
    t_material mat = get_obj_material(object);
    if (!mat.is_checkerboard)
        return (mat.color);
    if (*(t_type *)object == PLANE)
        return (checker_plane((t_plane *)object, &mat, hit_point));
    if (*(t_type *)object == SPHERE)
        return (checker_sphere((t_sphere *)object, &mat, hit_point));
    if (*(t_type *)object == CYLINDER)
        return (checker_cylinder((t_cylinder *)object, &mat, hit_point));
    if (*(t_type *)object == CONE)
        return (checker_cone((t_cone *)object, &   mat, hit_point));
    return (mat.color);
}

static t_color phong_model(t_scene *scene, void *obj, t_material *material,
        t_point hit_point, t_ray *ray, t_list *lights)
{
    t_vec   normal = get_normal_any(obj, hit_point);
    t_vec   light_dir;
    t_vec   reflect_dir;
    t_list  *light_node = lights;
    t_color res = {0, 0, 0};
    double  diff;
    double  spec;
    double  t_shadow;
    void    *shadow_obj;
    t_color  obj_color = get_object_color(obj, hit_point);

    if (vec_dot(normal, ray->direction) > 0)
        normal = vec_mult(normal, -1.0);
    while (light_node)
    {
        if (*(t_type_light *)light_node->content == AMBIENT)
        {
            t_ambient *amb = (t_ambient *)light_node->content;
            res = c_add(res, c_mult(c_prod(obj_color, amb->color),
                        amb->ratio));
        }
        else
        {
            t_light *l = (t_light *)light_node->content;
            t_vec dist_vec = vec_sub(l->pos, hit_point);
            double d_light = vec_length(dist_vec);
            light_dir = vec_normalize(dist_vec);

            t_ray s_ray = {vec_add(hit_point, vec_mult(normal, EPSILON * 2.0)),
                light_dir};
            shadow_obj = find_closest_point(&s_ray, scene->objects, &t_shadow);
            double shadow_factor = 1.0;
            if (shadow_obj && t_shadow < d_light)
            {
                t_material s_mat = get_obj_material(shadow_obj);
                if (s_mat.transparency > 0)
                    shadow_factor = s_mat.transparency * 0.5;
                else
                    shadow_factor = 0.0;
            }
            if (shadow_factor > 0)
            {
                diff = fmax(vec_dot(normal, light_dir), 0.0);
                if (diff > 0)
                    res = c_add(res, c_mult(c_prod(obj_color, l->color),
                            diff * l->brightness * material->k_diff
                                * shadow_factor));           
                t_vec view_dir = vec_mult(ray->direction, -1.0);
                reflect_dir = vec_sub(vec_mult(normal, 2.0 * vec_dot(normal, light_dir)), light_dir);
                reflect_dir = vec_normalize(reflect_dir);
                spec = fmax(vec_dot(view_dir, reflect_dir), 0.0);
                if (spec > 0)
                    res = c_add(res, c_mult(l->color,
                        pow(spec, material->shinness) * l->brightness
                        * material->k_spec * shadow_factor));
            }
        }
        light_node = light_node->next;
    }
    return (res);
}

static t_ray calculate_refract(t_vec incident, t_vec normal,
        t_point hit_point, double ior)
{
    double  cos_i = fmin(vec_dot(vec_mult(incident, -1.0), normal), 1.0);
    double  eta = 1.0 / ior;
    t_ray   ray;

    if (vec_dot(incident, normal) > 0)
    {
        eta = ior;
        normal = vec_mult(normal, -1.0);
        cos_i = fmin(vec_dot(vec_mult(incident, -1.0), normal), 1.0);
    }
    double k = 1.0 - eta * eta * (1.0 - cos_i * cos_i);
    if (k < 0)
    {
        ray.direction = vector(0, 0, 0);
        return (ray);
    }
    ray.origin = vec_sub(hit_point, vec_mult(normal, EPSILON * 2.0));
    ray.direction = vec_normalize(vec_add(vec_mult(incident, eta),
                vec_mult(normal, (eta * cos_i - sqrt(k)))));
    return (ray);
}

t_color ray_color_recursive(t_scene *scene, t_ray ray, int depth)
{
    void        *object;
    double      t;
    t_material  mat;
    t_point     hit_point;
    t_color     final_c = {0,0,0};

    if (depth >= MAX_DEPTH)
        return ((t_color){0,0,0});

    object = find_closest_point(&ray, scene->objects, &t);
    if (!object)
        return (default_color(scene));
    mat = get_obj_material(object);
    hit_point = vec_add(ray.origin, vec_mult(ray.direction, t));
    t_color local = phong_model(scene, object, &mat, hit_point, &ray,
            scene->lights);

    if (mat.transparency > 0 || mat.k_spec > 0)
    {
        t_vec normal = get_normal_any(object, hit_point);
        t_color reflection = {0,0,0};
        t_color refraction = {0,0,0};
        if (mat.k_spec > 0)
        {
            t_vec r_dir = vec_normalize(vec_sub(ray.direction,
                    vec_mult(normal, 2.0 * vec_dot(normal, ray.direction))));
            t_ray r_ray = {vec_add(hit_point, vec_mult(normal, EPSILON * 2.0)),
                r_dir};
            reflection = ray_color_recursive(scene, r_ray, depth + 1);
        }
        if (mat.transparency > 0)
        {
            t_ray re_ray = calculate_refract(ray.direction, normal, hit_point,
                    mat.ior);
            if (vec_length(re_ray.direction) > 0)
                refraction = ray_color_recursive(scene, re_ray, depth + 1);
            /*else
            {
                t_vec r_dir = vec_normalize(vec_sub(ray.direction,
                    vec_mult(normal, 2.0 * vec_dot(normal, ray.direction))));
                t_ray r_ray = {vec_add(hit_point,
                        vec_mult(normal, EPSILON * 2.0)), r_dir};
                reflection = ray_color_recursive(scene, r_ray, depth + 1);
            }*/
        }
        final_c = c_add(c_mult(local, (1.0 - mat.transparency)),
                        c_mult(refraction, mat.transparency));
        final_c = c_add(final_c, c_mult(reflection, mat.k_spec));
    }
    else
        final_c = local;

    return (final_c);
}

int ray_color(t_scene *scene, t_ray ray)
{
    t_color res;

    res = ray_color_recursive(scene, ray, 0);
    return (color_to_int_local(res));
}

void put_pixel(t_img *img, int x, int y, int color)
{
    char    *dest;

    if (x >= 0 && x < img->image_width && y >= 0 && y < img->image_height)
    {
        dest = img->data
            + (y * img->size_line)
            + (x * (img->bit_per_pixel / 8));
        *(unsigned int *)dest = color;
    }
}
