/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone_cap_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:28 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 02:11:15 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

t_hit	cone_cap_intersection(t_object *obj, t_ray ray)
{
	t_hit	hit;
	t_hit	cap;
	t_vec3	hit_vector;

	hit = cone_intersection(obj, ray);
	cap = cap_intersection(obj->anti_normal, obj->position, obj->radius, ray);
	if (cap.is_valid && (!hit.is_valid || cap.distance < hit.distance))
	{
		hit.hit_point = cap.hit_point;
		hit.normal = obj->anti_normal;
		hit.distance = cap.distance;
		hit_vector = vec3_sub_vec3(cap.hit_point, obj->position);
		hit.uv_map = cap_map_uv(hit_vector, obj->orth_normal, obj->orth_normal2,
				obj->radius);
		hit.is_valid = TRUE;
	}
	return (hit);
}
