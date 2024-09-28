/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:08 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 12:53:34 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3.h"

t_vec3	vec3_cap(t_vec3 a, float min, float max)
{
	if (a.x < min)
		a.x = min;
	else if (a.x > max)
		a.x = max;
	if (a.y < min)
		a.y = min;
	else if (a.y > max)
		a.y = max;
	if (a.z < min)
		a.z = min;
	else if (a.z > max)
		a.z = max;
	return (a);
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_vec3	vec3_scale(t_vec3 a, float s)
{
	a.x *= s;
	a.y *= s;
	a.z *= s;
	return (a);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result);
}

t_vec3	vec3_normalize(t_vec3 a)
{
	float	mag;

	mag = vec3_magnitude(a);
	if (mag <= ZERO)
		return ((t_vec3){0, 0, 0});
	a.x /= mag;
	a.y /= mag;
	a.z /= mag;
	return (a);
}
