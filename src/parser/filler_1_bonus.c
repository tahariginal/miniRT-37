/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:45:45 by tkoulal           #+#    #+#             */
/*   Updated: 2024/09/28 14:45:50 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

int	fill_ambient(t_scene *scene, char **param, size_t count)
{
	t_vec3	color;
	float	intensity;

	if (count != 3)
		return (log_error("invalid number of params for ambient light"));
	if (get_float(&intensity, param[1]) || intensity < 0 || intensity > 1.0f)
		return (log_error("invalid intensity param for ambient light"));
	if (get_vec3(&color, param[2]) || is_valid_color(color))
		return (log_error("invalid color param for ambient light"));
	scene->ambient_color = vec3_scale(color, (1 / 255.0f) * intensity);
	return (0);
}

int	fill_light(t_parser *p, char **param, size_t count)
{
	t_light	light;
	t_vec3	position;
	float	intensity;
	t_vec3	color;

	if (count != 4)
		return (log_error("invalid number of params for light"));
	if (get_vec3(&position, param[1]))
		return (log_error("invalid position param for light"));
	if (get_float(&intensity, param[2]) || intensity < 0 || intensity > 1.0f)
		return (log_error("invalid intensity param for light"));
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return (log_error("invalid color param for light"));
	light = new_light(position, intensity, color);
	if (add_to_arr(&p->lights, &light) == NULL)
		return (log_error("Malloc failed"));
	return (0);
}

int	fill_camera(t_scene *scene, char **param, size_t count)
{
	t_vec3	position;
	t_vec3	orientation;
	float	fov;

	if (count != 4)
		return (log_error("invalid number of params for camera"));
	if (get_vec3(&position, param[1]))
		return (log_error("invalid position param for camera"));
	if (get_vec3(&orientation, param[2]))
		return (log_error("invalid orientation param for camera"));
	if (get_float(&fov, param[3]) || fov > 180.0f || fov < 0)
		return (log_error("invalid fov param for camera"));
	scene->camera = new_camera(position, orientation, (float)WIN_HEIGHT
			/ WIN_WIDTH, fov);
	return (0);
}

int	fill_sphere(t_parser *p, char **param, size_t count)
{
	t_object	object;
	t_vec3		position;
	float		diameter;
	t_vec3		color;

	if (count < 4)
		return (log_error("invalid number of params for sphere"));
	if (get_vec3(&position, param[1]))
		return (log_error("invalid position param for sphere"));
	if (get_float(&diameter, param[2]) || diameter < 0)
		return (log_error("invalid diameter param for sphere"));
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return (log_error("invalid color param for sphere"));
	object = new_sphere(position, diameter / 2, color);
	if (count > 4 && fill_object_params(&object, param + 4))
		return (1);
	if (add_to_arr(&p->objects, &object) == NULL)
		return (log_error("Malloc failed"));
	return (0);
}
