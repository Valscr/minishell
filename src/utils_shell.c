/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:01:51 by valentin          #+#    #+#             */
/*   Updated: 2023/03/12 21:31:22 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_empty_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

char	*init_shell(void)
{
	char	*dest;
	char	*true;
	char	*false;
	char	*prompt;

	true = ft_strdup("\001\033[1;90m\002○\001\033[0m\002 ");
	if (true == 0)
		return (NULL);
	false = ft_strdup("\001\033[1;31m\002○\001\033[0m\002 ");
	if (false == 0)
		return (NULL);
	prompt = ft_strdup("\001\033[1;94m\002minishell\001\033[0m\002$ ");
	if (prompt == 0)
		return (NULL);
	signal(SIGINT, (void (*)(int))ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	if (g_sig.code_error == 0)
		dest = ft_strjoin(true, prompt);
	else
		dest = ft_strjoin(false, prompt);
	free(true);
	free(false);
	free(prompt);
	return (dest);
}
