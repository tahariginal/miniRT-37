/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:08 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 12:53:15 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3.h"

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

float	vec3_magnitude(t_vec3 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec4	vec3_to_vec4(t_vec3 a, float w)
{
	t_vec4	res;

	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
	res.w = w;
	return (res);
}

t_vec3	vec4_to_vec3(t_vec4 a)
{
	t_vec3	res;

	res.x = a.x;
	res.y = a.y;
	res.z = a.z;
	return (res);
}
