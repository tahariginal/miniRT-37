/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:17:24 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 03:23:15 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.h"

void	calculate_camera_uv(t_camera *camera)
{
	camera->forward = vec3_normalize(camera->forward);
	camera->u = vec3_cross(camera->forward, (t_vec3){0.0f, 0.0f, 1.0f});
	if (vec3_magnitude(camera->u) <= ZERO)
		camera->u = vec3_cross(camera->forward, (t_vec3){0.0f, 1.0f, 0.0f});
	camera->u = vec3_scale(camera->u, sinf((camera->fov / 180.0f) * (PI / 2)));
	camera->v = vec3_cross(camera->u, camera->forward);
	camera->v = vec3_scale(camera->v, camera->aspect_ratio);
}

t_camera	new_camera(t_vec3 origin, t_vec3 orientation, float aspect_ratio,
		float fov)
{
	t_camera	camera;

	camera.origin = origin;
	camera.forward = vec3_normalize(orientation);
	camera.aspect_ratio = aspect_ratio;
	camera.fov = fov;
	calculate_camera_uv(&camera);
	return (camera);
}
