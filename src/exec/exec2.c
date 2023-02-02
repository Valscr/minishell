/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:21:16 by valentin          #+#    #+#             */
/*   Updated: 2023/02/03 00:04:49 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_fonct(t_data *data, char *argv)
{	
	int	i;
	int	red;
	int	status;

	i = 0;
	red = 0;
	if (iter_pipe(argv) > 1)
	{
		close_pipes(data, iter_pipe(argv));
		while (i++ < 2 * (iter_pipe(argv) - 1))
			waitpid(g_sig.pid, &status, 0);
		parent_free(data);
	}
	else
		waitpid(g_sig.pid, &status, 0);
	if (WIFEXITED(status))
	{
		red = WEXITSTATUS(status);
		return (red);
	}
	return (0);
}

char	*replace_code_error(char *str, int i)
{
	char	*dest;
	char	*code_error;
	int		j;
	int		y;

	j = 0;
	y = 0;
	code_error = ft_itoa(g_sig.code_error);
	dest = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(code_error) + 1));
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	while (y < ft_strlen(code_error))
		dest[j++] = code_error[y++];
	i += ft_strlen(code_error) + 1;
	if (str[i - 2])
	{
		while (str[i])
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	return (free_str(code_error), free_str(str), dest);
}
