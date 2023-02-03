/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:24:48 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 02:06:05 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_c_handler(int sig)
{
	(void)sig;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", 1);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.code_error = 1;
	}
	else
	{
		ft_putstr_fd("\b\b  ", 1);
		ft_putstr_fd("\n", 1);
		g_sig.code_error = 130;
	}
	g_sig.sigint = 1;
	return ;
}

void	ctrl_c2_handler(int sig)
{
	(void)sig;
	exit(130);
	return ;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", 1);
		ft_putendl_fd(nbr, 1);
		g_sig.code_error = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 1);
	free_str(nbr);
	return ;
}
