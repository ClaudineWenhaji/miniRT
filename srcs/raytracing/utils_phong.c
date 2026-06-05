/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:42:08 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/05 17:43:49 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_diffuse(t_phong *p, t_light_ctx *ctx)
{
	double	diff;

	diff = fmax(vec_dot(p->normal, ctx->light_dir), 0.0);
	if (diff <= 0.0)
		return ((t_color){0, 0, 0});
	return (c_mult(
			c_prod(p->obj_color, ctx->light->color),
			diff
			* ctx->light->brightness
			* p->material->k_diff
			* ctx->shadow));
}

t_color	get_specular(t_phong *p, t_light_ctx *ctx)
{
	t_vec	reflect;
	t_vec	view;
	double	spec;

	view = vec_mult(p->ray.direction, -1.0);
	reflect = vec_sub(
			vec_mult(p->normal,
				2.0 * vec_dot(p->normal, ctx->light_dir)),
			ctx->light_dir);
	spec = fmax(vec_dot(view,
				vec_normalize(reflect)), 0.0);
	if (spec <= 0.0)
		return ((t_color){0, 0, 0});
	return (c_mult(ctx->light->color,
			pow(spec, p->material->shinness)
			* ctx->light->brightness
			* p->material->k_spec
			* ctx->shadow));
}
