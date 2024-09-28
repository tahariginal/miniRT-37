/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:40 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 03:45:24 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

t_hit	cap_intersection(t_vec3 cap_normal, t_vec3 cap_center, float radius,
		t_ray ray)
{
	float	dot_na;
	float	dot_nd;
	float	dot_np;
	t_hit	hit;
	float	t;

	hit.is_valid = FALSE;
	dot_nd = vec3_dot(cap_normal, ray.dir);
	if (fabs(dot_nd) > ZERO)
	{
		dot_na = vec3_dot(cap_normal, ray.origin);
		dot_np = vec3_dot(cap_normal, cap_center);
		t = (dot_np - dot_na) / dot_nd;
		if (t <= CAM_CLIP)
			return (hit);
		hit.hit_point = vec3_scale(ray.dir, t);
		hit.hit_point = vec3_add_vec3(hit.hit_point, ray.origin);
		hit.distance = vec3_magnitude(vec3_sub_vec3(hit.hit_point, ray.origin));
		if (vec3_magnitude(vec3_sub_vec3(hit.hit_point, cap_center)) <= radius)
			hit.is_valid = TRUE;
	}
	return (hit);
}

t_vec4	cap_map_uv(t_vec3 vec, t_vec3 u, t_vec3 v, float radius)
{
	t_vec4	uv_map;

	uv_map.z = vec3_dot(vec, u);
	uv_map.w = vec3_dot(vec, v);
	uv_map.x = (uv_map.z / radius) * 0.5f + 0.5f;
	uv_map.y = (uv_map.w / radius) * 0.5f + 0.5f;
	return (uv_map);
}

int	set_objects_textures(void *mlx, t_scene *scene)
{
	t_object	*obj;
	size_t		i;

	i = 0;
	while (i < scene->objects_count)
	{
		obj = scene->objects + i;
		if (obj->texture.filename != NULL && open_texture(mlx,
				&obj->texture) == NULL)
			return (printf(RED "Can't open texture [%s]\n" RST,
					obj->texture.filename));
		if (obj->normal_map.filename != NULL && open_texture(mlx,
				&obj->normal_map) == NULL)
			return (printf(RED "Can't open texture [%s]\n" RST,
					obj->texture.filename));
		i++;
	}
	free_textures_filenames(scene);
	return (0);
}

void	solve_quad_eq(t_quad_eq eq, t_hit *hit, t_ray ray)
{
	if (eq.det == ZERO)
		eq.t = -eq.b / (2 * eq.a);
	else if (eq.det > ZERO)
	{
		eq.t = (-eq.b - sqrtf(eq.det)) / (2 * eq.a);
		if (eq.t <= CAM_CLIP)
			eq.t = (-eq.b + sqrtf(eq.det)) / (2 * eq.a);
	}
	if (eq.det >= ZERO && eq.t > CAM_CLIP)
	{
		hit->hit_point = vec3_scale(ray.dir, eq.t);
		hit->hit_point = vec3_add_vec3(hit->hit_point, ray.origin);
		hit->distance = vec3_magnitude(vec3_sub_vec3(ray.origin,
					hit->hit_point));
		hit->is_valid = TRUE;
	}
}

t_vec3	get_object_color(t_hit hit)
{
	t_vec3	color;
	int		x;
	int		y;

	color = hit.object->color;
	if (hit.object->checkerboard)
	{
		x = ceil(hit.uv_map.z);
		y = ceil(hit.uv_map.w);
		if ((y + x) % 2 == 0)
			color = (t_vec3){0};
		else
			color = (t_vec3){1, 1, 1};
	}
	else if (hit.object->texture.data != NULL)
	{
		x = hit.uv_map.x * hit.object->texture.width;
		y = hit.uv_map.y * hit.object->texture.height;
		x = int_cap(x, 0, hit.object->texture.width - 1);
		y = int_cap(y, 0, hit.object->texture.height - 1);
		x = get_img_pixel_at(&hit.object->texture, x, y);
		color = vec3_scale(get_vec3_color(x), 1 / 255.0f);
	}
	return (color);
}
