/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:46:04 by tkoulal           #+#    #+#             */
/*   Updated: 2024/09/28 14:46:06 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	fill_cylinder(t_parser *p, char **param, size_t count)
{
	t_object	o;
	t_vec3		height_diam;

	if (count != 6)
		return (log_error("invalid number of params for cylinder"));
	if (get_vec3(&o.position, param[1]))
		return (log_error("invalid point param for cylinder"));
	if (get_vec3(&o.normal, param[2]) || is_normalized(o.normal) == 0)
		return (log_error("invalid normal param for cylinder"));
	if (get_float(&height_diam.x, param[3]) || height_diam.x < 0)
		return (log_error("invalid height param for cylinder"));
	if (get_float(&height_diam.y, param[4]) || height_diam.y < 0)
		return (log_error("invalid diameter param for cylinder"));
	if (get_vec3(&o.color, param[5]) || is_valid_color(o.color))
		return (log_error("invalid color param for cylinder"));
	o = new_cylinder(o.normal, o.position, height_diam, o.color);
	if (add_to_arr(&p->objects, &o) == NULL)
		return (log_error("Malloc failed"));
	return (0);
}
