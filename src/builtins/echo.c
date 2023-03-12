/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:13:31 by valentin          #+#    #+#             */
/*   Updated: 2023/03/12 23:50:00 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	ft_echo(char **args)
{
	int		i;
	int		d;
	int		n_option;

	i = 0;
	d = 0;
	n_option = 0;
	if (nb_args(args) > 0)
	{
		while (args[i][d] == ' ')
			d++;
		if (args[i][d] == '-' && args[i][d + 1] == 'n' && (args[i][d + 2] == 'n' || args[i][d + 2] == ' '))
		{
			n_option = 1;
			d += 2;
			while (args[i][d] == 'n')
				d++;
		}
		d++;
		while (args[i])
		{
			while (args[i][d])
				write(STDOUT, &args[i][d++], 1);
			i++;
			d = 0;
		}
	}
	if (n_option == 0)
		write(STDOUT, "\n", 1);
	free_tab_str(args);
	return (0);
}
