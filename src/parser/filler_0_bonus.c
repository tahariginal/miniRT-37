/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_0_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:45:16 by tkoulal           #+#    #+#             */
/*   Updated: 2024/09/28 14:45:53 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

int	fill_object_params_1(t_object *obj, char ***param)
{
	if (ft_strcmp(**param, "-t") == 0)
	{
		if (obj->texture.filename != NULL)
			return (log_error("multiple texture img provided."));
		(*param)++;
		if (*param == NULL)
			return (log_error("provide a path to the xpm texture img."));
		obj->texture.filename = ft_strdup(**param);
		if (obj->texture.filename == NULL)
			return (log_error("Malloc failed"));
	}
	else if (ft_strcmp(**param, "-n") == 0)
	{
		if (obj->normal_map.filename != NULL)
			return (log_error("multiple normal img provided."));
		(*param)++;
		if (*param == NULL)
			return (log_error("provide a path to the xpm normal map."));
		obj->normal_map.filename = ft_strdup(**param);
		if (obj->normal_map.filename == NULL)
			return (log_error("Malloc failed"));
	}
	else
		return (log_error("Invalid param"));
	return (SUCESS);
}

int	fill_object_params(t_object *obj, char **param)
{
	while (param && *param)
	{
		if (ft_strcmp(*param, "-c") == 0)
		{
			obj->checkerboard = TRUE;
		}
		else if (ft_strcmp(*param, "-h") == 0)
		{
			obj->hidden = TRUE;
		}
		else if (ft_strcmp(*param, "-r") == 0)
		{
			param++;
			if (get_float(&obj->reflection, *param) || obj->reflection < 0
				|| obj->reflection > 1.0f)
				return (log_error("provide a reflection value [0.0 ~ 1.0]."));
		}
		else if (fill_object_params_1(obj, &param))
			return (ERROR);
		param++;
	}
	return (0);
}
