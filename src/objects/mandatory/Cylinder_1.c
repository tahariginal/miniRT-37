/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:34 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 04:25:02 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

void	cylinder_caps(t_hit *hit, t_object *o, t_ray ray)
{
	t_hit	cap;
	t_hit	top_cap;
	t_hit	dwn_cap;

	cap.is_valid = FALSE;
	top_cap = cap_intersection(o->normal, o->top_cap_center, o->radius, ray);
	top_cap.normal = o->normal;
	dwn_cap = cap_intersection(o->normal, o->bottom_cap_center, o->radius, ray);
	dwn_cap.normal = o->anti_normal;
	if (top_cap.is_valid && (!dwn_cap.is_valid
			|| top_cap.distance < dwn_cap.distance))
		cap = top_cap;
	else if (dwn_cap.is_valid && (!top_cap.is_valid
			|| dwn_cap.distance < top_cap.distance))
		cap = dwn_cap;
	if (cap.is_valid && (!hit->is_valid || cap.distance < hit->distance))
	{
		hit->hit_point = cap.hit_point;
		hit->normal = cap.normal;
		hit->distance = cap.distance;
		hit->uv_map = cap_map_uv(vec3_sub_vec3(cap.hit_point, o->position),
				o->orth_normal, o->orth_normal2, o->radius);
		hit->is_valid = TRUE;
	}
}

void	cylinder_recalculate(t_object *obj)
{
	obj->anti_normal = vec3_scale(obj->normal, -1);
	obj->top_cap_center = vec3_add_vec3(obj->position, vec3_scale(obj->normal,
				obj->height / 2));
	obj->bottom_cap_center = vec3_add_vec3(obj->position,
			vec3_scale(obj->anti_normal, obj->height / 2));
}

t_object	new_cylinder(t_vec3 normal, t_vec3 center, t_vec3 height_diameter,
		t_vec3 color)
{
	t_object	cylinder;

	cylinder = (t_object){0};
	cylinder.type = OBJ_CYLINDER;
	cylinder.intersection = &cylinder_intersection;
	cylinder.recalculate = &cylinder_recalculate;
	cylinder.position = center;
	cylinder.normal = vec3_normalize(normal);
	cylinder.height = height_diameter.x;
	cylinder.radius = height_diameter.y / 2;
	cylinder.color = vec3_scale(color, 1.0f / 255.0f);
	cylinder.orth_normal = vec3_normalize(vec3_cross(cylinder.normal,
				(t_vec3){0.0f, 1.0f, 0.0f}));
	if (vec3_magnitude(cylinder.orth_normal) <= ZERO)
		cylinder.orth_normal = vec3_normalize(vec3_cross(cylinder.normal,
					(t_vec3){0.0f, 0.0f, 1.0f}));
	cylinder.orth_normal2 = vec3_cross(cylinder.normal, cylinder.orth_normal);
	cylinder_recalculate(&cylinder);
	return (cylinder);
}
