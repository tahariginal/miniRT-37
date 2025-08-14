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

void	rotate_axis(t_vec3 normal, t_vec3 *u, t_vec3 *v, float angle)
{
	t_vec3	r_u;
	t_vec3	r_v;
	t_vec3	tmp;

	tmp = vec3_scale(*u, cosf((angle / 180) * PI));
	r_u = vec3_scale(*v, sinf((angle / 180) * PI));
	r_u = vec3_add_vec3(tmp, r_u);
	r_v = vec3_cross(r_u, normal);
	*u = r_u;
	*v = r_v;
}
