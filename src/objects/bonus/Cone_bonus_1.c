/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone_bonus_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:26 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 03:38:55 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

void	cone_recalculate(t_object *obj)
{
	obj->anti_normal = vec3_scale(obj->normal, -1);
	obj->orth_normal = vec3_cross(obj->normal, (t_vec3){1.0f, 0.0f, 0.0f});
	if (vec3_magnitude(obj->orth_normal) <= ZERO)
		obj->orth_normal = vec3_cross(obj->normal, (t_vec3){0.0f, 0.0f, 1.0f});
	obj->orth_normal = vec3_normalize(obj->orth_normal);
	obj->orth_normal2 = vec3_cross(obj->normal, obj->orth_normal);
	obj->cone_tip = vec3_scale(obj->normal, obj->height);
	obj->cone_tip = vec3_add_vec3(obj->position, obj->cone_tip);
}

t_vec4	cone_map_uv(t_hit hit, t_object *obj)
{
	t_vec4	map;
	t_vec3	point_vector;
	float	dot_ort1;
	float	dot_ort2;

	point_vector = vec3_sub_vec3(hit.hit_point, obj->position);
	dot_ort1 = vec3_dot(obj->orth_normal, point_vector);
	dot_ort2 = vec3_dot(obj->orth_normal2, point_vector);
	map.z = obj->radius;
	map.z *= atan2f(-dot_ort1, dot_ort2);
	map.x = map.z / (obj->radius * PI);
	map.x = map.x * 0.5f + 0.5f;
	map.w = vec3_dot(obj->normal, point_vector);
	map.y = 1.0f - map.w / obj->height;
	return (map);
}

t_quad_eq	calculate_cone_quad(t_object *obj, t_ray ray)
{
	t_quad_eq	eq;
	t_vec3		w;
	float		m;
	float		dot_rdn;
	float		dot_wn;

	m = vec3_magnitude(vec3_scale(obj->normal, obj->height));
	m = (obj->radius * obj->radius) / (m * m);
	w = vec3_sub_vec3(ray.origin, obj->cone_tip);
	dot_rdn = vec3_dot(ray.dir, obj->normal);
	dot_wn = vec3_dot(w, obj->normal);
	eq.a = vec3_dot(ray.dir, ray.dir) - m * (dot_rdn * dot_rdn);
	eq.a -= (dot_rdn * dot_rdn);
	eq.b = vec3_dot(ray.dir, w) - m * (dot_rdn * dot_wn);
	eq.b -= dot_rdn * dot_wn;
	eq.b *= 2.0f;
	eq.c = vec3_dot(w, w) - m * (dot_wn * dot_wn) - (dot_wn * dot_wn);
	eq.det = (eq.b * eq.b) - (4.0f * eq.a * eq.c);
	return (eq);
}

void	chop_cone(t_quad_eq eq, t_hit *hit, t_object *obj, t_ray ray)
{
	t_vec3	hitpoint_vector;
	float	origin_distance;
	float	t;

	hitpoint_vector = vec3_sub_vec3(hit->hit_point, obj->position);
	origin_distance = vec3_dot(hitpoint_vector, obj->normal);
	if (origin_distance < ZERO || origin_distance > obj->height)
	{
		if (eq.det > ZERO)
		{
			t = (-eq.b + sqrtf(eq.det)) / (2 * eq.a);
			if (eq.t != t)
			{
				hit->hit_point = vec3_scale(ray.dir, t);
				hit->hit_point = vec3_add_vec3(hit->hit_point, ray.origin);
				hit->distance = vec3_magnitude(vec3_sub_vec3(ray.origin,
							hit->hit_point));
				hitpoint_vector = vec3_sub_vec3(hit->hit_point, obj->position);
				origin_distance = vec3_dot(hitpoint_vector, obj->normal);
			}
		}
		if (origin_distance < ZERO || origin_distance > obj->height)
			hit->is_valid = FALSE;
	}
}

t_hit	cone_intersection(t_object *object, t_ray ray)
{
	t_hit		hit;
	t_quad_eq	eq;

	hit.object = object;
	hit.is_valid = FALSE;
	eq = calculate_cone_quad(object, ray);
	solve_quad_eq(eq, &hit, ray);
	if (hit.is_valid)
		chop_cone(eq, &hit, object, ray);
	if (hit.is_valid == FALSE)
		return (hit);
	hit.normal = vec3_normalize(vec3_sub_vec3(hit.hit_point, object->position));
	hit.uv_map = cone_map_uv(hit, object);
	return (hit);
}
