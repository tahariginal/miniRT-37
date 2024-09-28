/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:40 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 03:38:45 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

t_vec3	get_axis_rotation(t_vec3 normalized_orientation, t_vec3 axis)
{
	float	cos_theta;
	float	sin_theta;

	cos_theta = vec3_dot(axis, normalized_orientation);
	sin_theta = sqrtf(1 - cos_theta * cos_theta);
	return (vec3_f(cos_theta, sin_theta, 0));
}

t_mat4x4	get_x_rotation_matrix(float angle)
{
	t_mat4x4	x_rot;
	float		cos;
	float		sin;

	cos = cosf((angle / 180) * PI);
	sin = sinf((angle / 180) * PI);
	x_rot = mat_id();
	*mat_at(&x_rot, 1, 1) = cos;
	*mat_at(&x_rot, 1, 2) = -sin;
	*mat_at(&x_rot, 2, 1) = sin;
	*mat_at(&x_rot, 2, 2) = cos;
	return (x_rot);
}

t_mat4x4	get_y_rotation_matrix(float angle)
{
	t_mat4x4	y_rot;
	float		cos;
	float		sin;

	cos = cosf((angle / 180) * PI);
	sin = sinf((angle / 180) * PI);
	y_rot = mat_id();
	*mat_at(&y_rot, 0, 0) = cos;
	*mat_at(&y_rot, 0, 2) = sin;
	*mat_at(&y_rot, 2, 0) = -sin;
	*mat_at(&y_rot, 2, 2) = cos;
	return (y_rot);
}

t_mat4x4	get_z_rotation_matrix(float angle)
{
	t_mat4x4	z_rot;
	float		cos;
	float		sin;

	cos = cosf((angle / 180) * PI);
	sin = sinf((angle / 180) * PI);
	z_rot = mat_id();
	*mat_at(&z_rot, 0, 0) = cos;
	*mat_at(&z_rot, 0, 1) = -sin;
	*mat_at(&z_rot, 1, 0) = sin;
	*mat_at(&z_rot, 1, 1) = cos;
	return (z_rot);
}
