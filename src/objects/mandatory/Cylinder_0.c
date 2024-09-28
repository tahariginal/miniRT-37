/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:34 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 04:24:59 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

t_vec4	cylinder_map_uv(t_hit hit, t_object *obj)
{
	t_vec4	map;
	t_vec3	point_vector;
	float	dot_ort1;
	float	dot_ort2;

	point_vector = vec3_sub_vec3(hit.hit_point, obj->position);
	dot_ort1 = vec3_dot(obj->orth_normal, point_vector);
	dot_ort2 = vec3_dot(obj->orth_normal2, point_vector);
	map.z = obj->radius * atan2f(-dot_ort1, dot_ort2);
	map.x = map.z / (obj->radius * PI);
	map.x = map.x * 0.5f + 0.5f;
	map.w = vec3_dot(obj->anti_normal, point_vector);
	map.y = map.w / (obj->height / 2);
	map.y = map.y * 0.5f + 0.5f;
	return (map);
}

t_vec3	cylinder_point_normal(t_hit hit_point, t_object *object)
{
	t_vec3	p;
	float	p_height;

	p = vec3_sub_vec3(hit_point.hit_point, object->position);
	p_height = vec3_dot(p, object->normal);
	p = vec3_add_vec3(object->position, vec3_scale(object->normal, p_height));
	return (vec3_normalize(vec3_sub_vec3(hit_point.hit_point, p)));
}

t_quad_eq	calculate_cylinder_quad(t_object *obj, t_ray ray)
{
	t_vec3		w;
	t_quad_eq	eq;
	float		dot_rdn;
	float		dot_wn;

	w = vec3_sub_vec3(ray.origin, obj->position);
	dot_rdn = vec3_dot(ray.dir, obj->normal);
	dot_wn = vec3_dot(w, obj->normal);
	eq.a = vec3_dot(ray.dir, ray.dir) - (dot_rdn * dot_rdn);
	eq.b = 2 * (vec3_dot(ray.dir, w) - (dot_rdn * dot_wn));
	eq.c = vec3_dot(w, w) - (dot_wn * dot_wn) - (obj->radius * obj->radius);
	eq.det = (eq.b * eq.b) - (4.0f * eq.a * eq.c);
	return (eq);
}

void	chop_cylinder(t_quad_eq eq, t_hit *hit, t_object *obj, t_ray ray)
{
	t_vec3	hitpoint_vector;
	float	origin_distance;
	float	t;

	hitpoint_vector = vec3_sub_vec3(hit->hit_point, obj->position);
	origin_distance = vec3_dot(hitpoint_vector, obj->normal);
	t = eq.t;
	if (fabs(origin_distance) > obj->height / 2)
	{
		if (eq.det > ZERO)
		{
			t = (-eq.b + sqrtf(eq.det)) / (2 * eq.a);
			if (eq.t != t)
			{
				hit->hit_point = vec3_scale(ray.dir, t);
				hit->hit_point = vec3_add_vec3(hit->hit_point, ray.origin);
				hitpoint_vector = vec3_sub_vec3(hit->hit_point, obj->position);
				origin_distance = vec3_dot(hitpoint_vector, obj->normal);
				hit->distance = vec3_magnitude(vec3_sub_vec3(ray.origin,
							hit->hit_point));
			}
		}
		if (eq.t == t || fabs(origin_distance) > obj->height / 2)
			hit->is_valid = FALSE;
	}
}

t_hit	cylinder_intersection(t_object *object, t_ray ray)
{
	t_quad_eq	eq;
	t_hit		hit;

	hit.object = object;
	hit.is_valid = FALSE;
	eq = calculate_cylinder_quad(object, ray);
	solve_quad_eq(eq, &hit, ray);
	if (hit.is_valid)
		chop_cylinder(eq, &hit, object, ray);
	if (hit.is_valid)
	{
		hit.normal = cylinder_point_normal(hit, object);
		hit.uv_map = cylinder_map_uv(hit, object);
	}
	cylinder_caps(&hit, object, ray);
	return (hit);
}
