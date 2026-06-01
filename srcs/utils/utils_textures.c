/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:28:28 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/29 13:11:59 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_texture	*get_texture(t_scene *scene, char *path)
{
	t_texture	*texture;
	int			len;

	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	texture = (t_texture *)malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->img_ptr = mlx_xpm_file_to_image(scene->window->mlx, path,
			&(texture->image_width), &(texture->image_height));
	if (!texture->img_ptr)
		return (printf("Error\ncheck the path to texture: [%s]\n", path),
				free(texture), NULL);
	texture->data = mlx_get_data_addr(texture->img_ptr,
			&texture->bit_per_pixel, &texture->size_line, &texture->endian);
	return (texture);
}

t_color	get_color_from_texture(t_vec normal, t_point hit_point, void *object,
		t_texture *texture, t_material *material)
{
	double		u;
	double		v;
	t_vec		u_dir;
	t_vec		v_dir;
	t_vec		reference;
	int			color;
	int			pixel[2];

	if (*(t_type *)object != SPHERE && *(t_type *)object != PLANE)
		return (material->color);
	if (*(t_type *)object == SPHERE)
	{
		u = 0.5 + atan2(normal.x, normal.z) / (2.0 * PI);
		v = acos(fmin(1.0, fmax(-1.0, normal.y))) / PI;
	}
	else
	{
		if (fabs(normal.y) > 0.9)
			reference = vector(0, 0, 1);
		else
			reference = vector(0, 1, 0);
		u_dir = vec_normalize(vec_cross_prod(reference, normal));
		v_dir = vec_cross_prod(normal, u_dir);
		u = vec_dot(vec_sub(hit_point, ((t_plane *)object)->point), u_dir);
		v = vec_dot(vec_sub(hit_point, ((t_plane *)object)->point), v_dir);
		u = fmod(u, 1.0);
		v = fmod(v, 1.0);
		if (u < 0)
			u += 1.0;
		if (v < 0)
			v += 1.0;
	}
	pixel[0] = (int)(u * (texture->image_width - 1));
	pixel[1] = (int)(v * (texture->image_height - 1));
	color = *(int *)(texture->data + (pixel[1] * texture->size_line
				+ pixel[0] * (texture->bit_per_pixel / 8)));
	return (int_to_color(color));
}
