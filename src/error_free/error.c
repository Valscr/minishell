/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 02:39:45 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 00:04:18 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	write_error(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		write(2, &str[i++], 1);
	return (0);
}

int	write_perror(char *str)
{
	perror(str);
	return (0);
}
