/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:13:31 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/19 01:37:51 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_free_table(void **table, int len)
{
	int	i;

	i = -1;
	if (len < 0)
		len = INT_MAX;
	while (table[++i] && i < len)
		free(table[i]);
}

double	ft_atod(char *number)
{
	char	**parts;
	double	integer_part;
	double	decimal_part;
	double	sign;
	int		i;

	sign = 1.0;
	if (*number == '-')
	{
		sign = -1.0;
		number++;
	}
	parts = ft_split(number, '.');
	if (!parts)
		return (0);
	integer_part = (double)ft_atoi(parts[0]);
	decimal_part = 0.0;
	if (parts[1])
	{
		decimal_part = (double)ft_atoi(parts[1]);
		i = -1;
		while (parts[1][++i])
			decimal_part /= 10.0;
	}
	ft_free_table((void **)parts, -1);
	return (sign * (integer_part + decimal_part));
}

void	clean_window(t_win *window)
{
	if (!window)
		return ;
	if (window->img)
	{
		mlx_destroy_image(window->mlx, window->img->img_ptr);
		free(window->img);
	}
	if (window->win)
		mlx_destroy_window(window->mlx, window->win);
	if (window->mlx)
	{
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
	free(window);
}


void	ft_clean(t_scene **scene)
{
	ft_lstclear(&(*scene)->objects, free);
	ft_lstclear(&(*scene)->lights, free);
	clean_window((*scene)->window);
	free(*scene);
	*scene = NULL;
}

static void	print_vec(char *name, t_vec v)
{
	printf("  %s: %f, %f, %f\n", name, v.x, v.y, v.z);
}

static void	print_color(t_color c)
{
	printf("  Color: %f, %f, %f\n", c.red, c.green, c.blue);
}

void	print_scene_info(t_scene *scene)
{
	t_list	*tmp;

	printf("--- Scene Info ---\n");
	printf("Camera:\n");
	print_vec("Pos", scene->camera.viewpoint);
	print_vec("Dir", scene->camera.direction);
	printf("  FOV: %f\n", scene->camera.fov);
	tmp = scene->lights;
	while (tmp)
	{
		t_type_light type = *(t_type_light *)tmp->content;
		if (type == AMBIENT)
		{
			t_ambient *a = (t_ambient *)tmp->content;
			printf("Ambient Light:\n");
			printf("  Ratio: %f\n", a->ratio);
			print_color(a->color);
		}
		else if (type == LIGHT)
		{
			t_light *l = (t_light *)tmp->content;
			printf("Point Light:\n");
			print_vec("Pos", l->pos);
			printf("  Brightness: %f\n", l->brightness);
			print_color(l->color);
		}
		tmp = tmp->next;
	}
	tmp = scene->objects;
	while (tmp)
	{
		t_type type = *(t_type *)tmp->content;
		if (type == SPHERE)
		{
			t_sphere *s = (t_sphere *)tmp->content;
			printf("Sphere:\n");
			print_vec("Center", s->center);
			printf("  Diameter: %f\n", s->diameter);
			print_color(s->color);
		}
		else if (type == PLANE)
		{
			t_plane *p = (t_plane *)tmp->content;
			printf("Plane:\n");
			print_vec("Point", p->point);
			print_vec("Normal", p->normal);
			print_color(p->color);
		}
		else if (type == CYLINDER)
		{
			t_cylinder *cy = (t_cylinder *)tmp->content;
			printf("Cylinder:\n");
			print_vec("Center", cy->center);
			print_vec("Axis", cy->axis);
			printf("  Diameter: %f, Height: %f\n", cy->diameter, cy->height);
			print_color(cy->color);
		}
		tmp = tmp->next;
	}
	printf("------------------\n");
}
