/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4x4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:16:10 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 12:51:11 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mat4x4.h"

t_mat4x4	mat_mul(t_mat4x4 *m1, t_mat4x4 *m2)
{
	t_mat4x4	res;
	int			row;
	int			col;
	int			i;

	res = (t_mat4x4){0};
	row = 0;
	while (row < MAT_ROWS)
	{
		col = 0;
		while (col < MAT_COLS)
		{
			i = 0;
			while (i < MAT_COLS)
			{
				*mat_at(&res, row, col) += *mat_at(m1, row, i) * *mat_at(m2, i,
					col);
				i++;
			}
			col++;
		}
		row++;
	}
	return (res);
}

t_vec3	mat_mul_vec3(t_mat4x4 *mat, t_vec3 *vec)
{
	t_vec4	result;
	float	sum;
	int		row;

	result = vec3_to_vec4(*vec, 1.0f);
	row = 0;
	while (row < MAT_ROWS)
	{
		sum = 0;
		sum += mat->data[row * MAT_COLS + 0] * result.x;
		sum += mat->data[row * MAT_COLS + 1] * result.y;
		sum += mat->data[row * MAT_COLS + 2] * result.z;
		sum += mat->data[row * MAT_COLS + 3] * result.w;
		*((float *)&result + row) = sum;
		row++;
	}
	return (vec4_to_vec3(result));
}

float	*mat_at(t_mat4x4 *mat, unsigned int row, unsigned int col)
{
	return (&(mat->data[(row * MAT_COLS) + col]));
}

t_mat4x4	mat_id(void)
{
	t_mat4x4		id;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < MAT_ROWS)
	{
		j = 0;
		while (j < MAT_COLS)
		{
			if (i == j)
				*mat_at(&id, i, j) = 1.0f;
			else
				*mat_at(&id, i, j) = 0.0f;
			j++;
		}
		i++;
	}
	return (id);
}
