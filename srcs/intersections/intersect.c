/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:47:15 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/22 17:57:15 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_object(void *object, t_ray *ray, double *t)
{
	if (*(t_type *)object == SPHERE)
		return (intersect_sphere((t_sphere *)object, ray, t));
	if (*(t_type *)object == CYLINDER)
		return (intersect_cylinder((t_cylinder *)object, ray, t));
	if (*(t_type *)object == PLANE)
		return (intersect_plane((t_plane *)object, ray, t));
	if (*(t_type *)object == CONE)
		return (intersect_cone((t_cone *)object, ray, t));
	return (0);
}
