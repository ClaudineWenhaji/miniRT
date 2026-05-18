/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:23:21 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/18 18:26:27 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_light(char **split_line, t_list **lights)
{
	void	*light;
	t_list	*node;

	light = NULL;
	if (ft_strcmp(split_line[0], "A") == 0)
		light = get_ambient_light(split_line);
	else
		light = get_normal_light(split_line);
	node = ft_lstnew(light);
	if (!node)
		return (free(light), 0);
	return (ft_lstadd_back(lights, node), 1);
}

static int	get_objects(char **split_line, t_list **objects)
{
	void	*object;
	t_list	*node;

	object = NULL;
	if (ft_strcmp(split_line[0], "sp") == 0)
		object = get_sphere(split_line);
	else if (ft_strcmp(split_line[0], "pl") == 0)
		object = get_plane(split_line);
	else if (ft_strcmp(split_line[0], "cy") == 0)
		object = get_cylinder(split_line);
	if (!object)
		return (0);
	node = ft_lstnew(object);
	if (!node)
		return (free(object), 0);
	return (ft_lstadd_back(objects, node), 1);
}

/*static int get_objects(char **split_line, t_list **objects)
{
    t_object   *object;
    t_sphere   *sphere;
    t_list     *node;

    object = NULL;

    if (ft_strcmp(split_line[0], "sp") == 0)
    {
        sphere = get_sphere(split_line);

        if (!sphere)
            return (0);

        object = malloc(sizeof(t_object));
        if (!object)
            return (free(sphere), 0);

        object->type = SPHERE;
        object->data = sphere;
        object->color = sphere->color;
    }

    node = ft_lstnew(object);

    if (!node)
        return (free(object), 0);

    ft_lstadd_back(objects, node);

    return (1);
}*/

static int split_and_get_scene(char *line, t_scene *scene)
{
	char	**split_line;
	int		result;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (perror("split:"), 0);
	if (ft_strcmp(split_line[0], "A") == 0
			|| ft_strcmp(split_line[0], "L") == 0)
		result = get_light(split_line, &scene->lights);
	else if (ft_strcmp(split_line[0], "C") == 0)
		result = get_camera(split_line, &scene->camera);
	else if (ft_strcmp(split_line[0], "pl") == 0
			|| ft_strcmp(split_line[0], "sp") == 0
			|| ft_strcmp(split_line[0], "cy") == 0
			|| ft_strcmp(split_line[0], "co") == 0)
		result = get_objects(split_line, &scene->objects);
	else
		return (ft_free_table((void **)split_line, -1), printf("Error\n"), 0);
	return (ft_free_table((void **)split_line, -1), result);
}

int	parsing(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		i;


	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\n"), 0);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'
					|| line[i] == '\n'))
			i++;
		if (line[i])
			if (!split_and_get_scene(line, scene))
				return (free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}
