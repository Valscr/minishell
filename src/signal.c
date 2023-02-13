/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:24:48 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 15:59:05 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_c_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig.code_error = 130;
	return ;
}

void	ctrl_c3_handler(int sig)
{
	(void)sig;
	g_sig.code_error = 130;
}

void	ctrl_c2_handler(int sig)
{
	(void)sig;
	close (0);
	g_sig.code_error = 130;
	return ;
}

void	sig_quit(int code)
{
	(void)code;
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_sig.code_error = 131;
	}
	return ;
}

void	sig_quit2(int code)
{
	(void)code;
	return ;
}
