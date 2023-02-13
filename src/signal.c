/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:24:48 by valentin          #+#    #+#             */
/*   Updated: 2023/02/13 19:17:45 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_c_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putstr_fd("\001\033[1;90m\002○\033[0m ", 1);
	rl_redisplay();
	g_sig.code_error = 130;
	return ;
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
	ft_putstr_fd("Quit (core dumped)\n", 1);
	g_sig.code_error = 131;
	return ;
}
