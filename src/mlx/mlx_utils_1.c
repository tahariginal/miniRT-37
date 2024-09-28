/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:16:05 by msitni            #+#    #+#             */
/*   Updated: 2024/09/28 03:42:03 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.h"
#include "input.h"

void	*open_texture(void *mlx_ptr, t_img *texture)
{
	texture->handle = mlx_xpm_file_to_image(mlx_ptr, texture->filename,
			&texture->width, &texture->height);
	if (texture->handle == NULL)
		return (NULL);
	texture->data = mlx_get_data_addr(texture->handle, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (texture->data);
}
