/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:47:34 by tkoulal           #+#    #+#             */
/*   Updated: 2024/09/28 14:47:35 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_line_2(char **param, size_t count, t_parser *parser)
{
	if (ft_strcmp(param[0], "pl") == 0)
	{
		if (fill_plane(parser, param, count))
			return (free_array(param), ERROR);
	}
	else if (ft_strcmp(param[0], "cy") == 0)
	{
		if (fill_cylinder(parser, param, count))
			return (free_array(param), ERROR);
	}
	else
	{
		log_error("invalid line");
		return (free_array(param), ERROR);
	}
	return (SUCESS);
}

int	check_line_1(char **param, size_t count, t_scene *scene, t_parser *parser)
{
	if (ft_strcmp(param[0], "C") == 0)
	{
		if (fill_camera(scene, param, count))
			return (free_array(param), ERROR);
		parser->camera_count++;
	}
	else if (ft_strcmp(param[0], "A") == 0)
	{
		if (fill_ambient(scene, param, count))
			return (free_array(param), ERROR);
		parser->ambient_count++;
	}
	else if (ft_strcmp(param[0], "L") == 0)
	{
		if (fill_light(parser, param, count))
			return (free_array(param), ERROR);
	}
	else if (ft_strcmp(param[0], "sp") == 0)
	{
		if (fill_sphere(parser, param, count))
			return (free_array(param), ERROR);
	}
	else
		return (check_line_2(param, count, parser));
	return (SUCESS);
}

int	check_line(char *line, t_scene *scene, t_parser *parser)
{
	char	**param;
	size_t	count;

	param = ft_split(line, &count, &ft_isspace);
	if (count == 0)
		return (free_array(param), SUCESS);
	if (check_line_1(param, count, scene, parser) == ERROR)
		return (ERROR);
	if (parser->ambient_count > 1 || parser->camera_count > 1
		|| parser->lights.count > 1)
	{
		log_error("multiple Capital params");
		log_error("Capital params are [Camera, Ambient light, Light]");
		return (free_array(param), ERROR);
	}
	return (free_array(param), SUCESS);
}

int	read_file(char *file, t_scene *scene, t_parser *parser)
{
	size_t	line_num;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (log_error("Scene file doesn't exist ):"), 1);
	line_num = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (check_line(line, scene, parser) == ERROR)
			return (error_in_line(line, fd, line_num));
		free(line);
		line = get_next_line(fd);
		line_num++;
	}
	close(fd);
	return (0);
}

int	parsing(t_scene *scene, char **av)
{
	t_parser	p;

	p = (t_parser){0};
	p.lights = init_da(sizeof(t_light));
	p.objects = init_da(sizeof(t_object));
	if (check_args(av[1]) == SUCESS)
	{
		if (read_file(av[1], scene, &p))
			return (ft_free(p.lights.data, p.objects.data, NULL), ERROR);
		scene->objects_count = p.objects.count;
		scene->objects = p.objects.data;
		scene->lights_count = p.lights.count;
		scene->lights = p.lights.data;
		if (p.ambient_count != 0 && p.camera_count != 0 && p.lights.count != 0)
			return (SUCESS);
		log_error("One or more Capital param is missing");
		log_error("Capital params are [Camera, Ambient light, Light]");
	}
	return (ERROR);
}
