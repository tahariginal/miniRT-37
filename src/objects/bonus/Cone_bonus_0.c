/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone_bonus_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:26 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 03:38:58 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

t_object	new_cone(t_vec3 normal, t_vec3 center, t_vec3 height_diameter,
		t_vec3 color)
{
	t_object	cone;

	cone = (t_object){0};
	cone.type = OBJ_CONE;
	cone.intersection = &cone_intersection;
	cone.recalculate = &cone_recalculate;
	cone.position = center;
	cone.normal = vec3_normalize(normal);
	cone.height = height_diameter.x;
	cone.radius = height_diameter.y / 2;
	cone.color = vec3_scale(color, 1.0f / 255.0f);
	cone.orth_normal = vec3_normalize(vec3_cross(cone.normal, (t_vec3){0.0f,
				1.0f, 0.0f}));
	if (vec3_magnitude(cone.orth_normal) <= ZERO)
		cone.orth_normal = vec3_normalize(vec3_cross(cone.normal, (t_vec3){0.0f,
					0.0f, 1.0f}));
	cone.orth_normal2 = vec3_cross(cone.normal, cone.orth_normal);
	cone_recalculate(&cone);
	return (cone);
}
