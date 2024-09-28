/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:47:17 by tkoulal           #+#    #+#             */
/*   Updated: 2024/09/28 14:47:18 by tkoulal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	f_slen(char *s)
{
	if (!*s)
		return (0);
	return (f_slen(s + 1) + 1);
}

int	f_is_rt_file(char *s, char *type)
{
	int	end1;
	int	end2;
	int	count;

	end1 = f_slen(s) - 1;
	end2 = f_slen(type) - 1;
	count = 3;
	while (end1 >= 0 && end2 >= 0 && s[end1] == type[end2] && count)
	{
		end1--;
		end2--;
		count--;
	}
	if (!count)
		return (0);
	return (1);
}

int	check_args(char *s)
{
	char	*type;

	type = ".rt";
	if (!f_is_rt_file(s, type))
		return (SUCESS);
	else
	{
		log_error("should enter .rt file :)");
		return (ERROR);
	}
}

int	error_in_line(char *line, int fd, size_t line_num)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf(RED "=: Error in line: %zu\n" RST, line_num);
	return (1);
}
