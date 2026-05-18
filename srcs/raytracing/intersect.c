/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:47:15 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/18 16:47:45 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int intersect_object(t_object *object, t_ray ray, double *t)
{
    if (object->type == SPHERE)
        return (intersect_sphere((t_sphere *)object->data, ray, t));
    /*else if (object->type == PLANE)
        return (intersect_plane((t_plane *)object->data, ray, t));
    else if (object->type == CYLINDER)
        return (intersect_cylinder((t_cylinder *)object->data, ray, t));
    else if (object->type == CONE)
        return (intersect_cone((t_cone *)object->data, ray, t));*/
    return (0); 
}