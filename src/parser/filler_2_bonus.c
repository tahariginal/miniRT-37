/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:46:16 by tkoulal           #+#    #+#             */
/*   Updated: 2024/09/28 14:46:20 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

int	fill_plane(t_parser *p, char **param, size_t count)
{
	t_object	object;
	t_vec3		point;
	t_vec3		normal;
	t_vec3		color;

	if (count < 4)
		return (log_error("invalid number of params for plane"));
	if (get_vec3(&point, param[1]))
		return (log_error("invalid point param for plane"));
	if (get_vec3(&normal, param[2]) || vec3_magnitude(normal) <= ZERO)
		return (log_error("invalid normal param for plane"));
	if (get_vec3(&color, param[3]) || is_valid_color(color))
		return (log_error("invalid color param for plane"));
	object = new_plane(point, normal, color);
	if (count > 4 && fill_object_params(&object, param + 4))
		return (1);
	if (add_to_arr(&p->objects, &object) == NULL)
		return (log_error("Malloc failed"));
	return (0);
}

int	fill_cylinder(t_parser *p, char **param, size_t count)
{
	t_object	o;
	t_vec3		height_diam;

	if (count < 6)
		return (log_error("invalid number of params for cylinder"));
	if (get_vec3(&o.position, param[1]))
		return (log_error("invalid point param for cylinder"));
	if (get_vec3(&o.normal, param[2]) || vec3_magnitude(o.normal) <= ZERO)
		return (log_error("invalid normal param for cylinder"));
	if (get_float(&height_diam.x, param[3]) || height_diam.x < 0)
		return (log_error("invalid height param for cylinder"));
	if (get_float(&height_diam.y, param[4]) || height_diam.y < 0)
		return (log_error("invalid diameter param for cylinder"));
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return (log_error("invalid color param for cylinder"));
	o = new_cylinder(o.normal, o.position, height_diam, o.color);
	if (count > 6 && fill_object_params(&o, param + 6))
		return (1);
	if (add_to_arr(&p->objects, &o) == NULL)
		return (log_error("Malloc failed"));
	return (0);
}

int	fill_rect(t_parser *p, char **param, size_t count)
{
	t_object	o;
	t_vec3		height_width;

	if (count < 6)
		return (log_error("invalid number of params for rectangle"));
	if (get_vec3(&o.position, param[1]))
		return (log_error("invalid point param for rectangle"));
	if (get_vec3(&o.normal, param[2]) || vec3_magnitude(o.normal) <= ZERO)
		return (log_error("invalid normal param for rectangle"));
	if (get_float(&height_width.x, param[3]) || height_width.x < 0)
		return (log_error("invalid width param for rectangle"));
	if (get_float(&height_width.y, param[4]) || height_width.y < 0)
		return (log_error("invalid height param for rectangle"));
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return (log_error("invalid color param for rectangle"));
	o = new_rect(o.position, o.normal, o.color, height_width);
	if (count > 6 && fill_object_params(&o, param + 6))
		return (1);
	if (add_to_arr(&p->objects, &o) == NULL)
		return (log_error("Malloc failed"));
	return (0);
}

int	fill_cone(t_parser *p, char **param, size_t count)
{
	t_object	o;
	t_vec3		height_diam;

	if (count < 6)
		return (log_error("invalid number of params for non cap cone"));
	if (get_vec3(&o.position, param[1]))
		return (log_error("invalid point param for non cap cone"));
	if (get_vec3(&o.normal, param[2]) || vec3_magnitude(o.normal) <= ZERO)
		return (log_error("invalid normal param for non cap cone"));
	if (get_float(&height_diam.x, param[3]) || height_diam.x < 0)
		return (log_error("invalid height param for non cap cone"));
	if (get_float(&height_diam.y, param[4]) || height_diam.y < 0)
		return (log_error("invalid diameter param for non cap cone"));
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return (log_error("invalid color param for non cap cone"));
	o = new_cone(o.normal, o.position, height_diam, o.color);
	if (count > 6 && fill_object_params(&o, param + 6))
		return (1);
	o.intersection = &cone_cap_intersection;
	if (add_to_arr(&p->objects, &o) == NULL)
		return (log_error("Malloc failed"));
	return (0);
}

int	fill_cone_cap(t_parser *p, char **param, size_t count)
{
	t_object	o;
	t_vec3		height_diam;

	if (count < 6)
		return (log_error("invalid number of params for capped cone"));
	if (get_vec3(&o.position, param[1]))
		return (log_error("invalid point param for capped cone"));
	if (get_vec3(&o.normal, param[2]) || vec3_magnitude(o.normal) <= ZERO)
		return (log_error("invalid normal param for capped cone"));
	if (get_float(&height_diam.x, param[3]) || height_diam.x < 0)
		return (log_error("invalid height param for capped cone"));
	if (get_float(&height_diam.y, param[4]) || height_diam.y < 0)
		return (log_error("invalid diameter param for capped cone"));
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return (log_error("invalid color param for capped cone"));
	o = new_cone(o.normal, o.position, height_diam, o.color);
	if (count > 6 && fill_object_params(&o, param + 6))
		return (1);
	if (add_to_arr(&p->objects, &o) == NULL)
		return (log_error("Malloc failed"));
	return (0);
}
