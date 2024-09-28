/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:21:51 by msitni            #+#    #+#             */
/*   Updated: 2024/09/27 13:23:16 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

int	log_error(const char *error)
{
	return (printf(RED "[ %s ]: ERROR: %s\n" RST, PROG_NAME, error));
}

int	log_debug(const char *msg)
{
	return (printf(YELLOW "[ %s ]: WARNING: %s\n" RST, PROG_NAME, msg));
}

int	log_info(const char *info)
{
	return (printf(GREEN "[ %s ]: INFO: %s\n" RST, PROG_NAME, info));
}
