/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:18:31 by valentin          #+#    #+#             */
/*   Updated: 2023/02/06 14:57:56 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_here_doc(t_data *data)
{
	data->infile = open(".heredoc_tmp", O_RDONLY);
	if (data->infile < 0)
		unlink(".heredoc_tmp");
	return ;
}

void	here_doc(char *argv, t_data *data)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file < 0)
		return ;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		buf = readline("> ");
		if (buf == NULL)
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free_str(buf);
	}
	free_str(buf);
	close(file);
	open_here_doc(data);
}

int	limiter_heredoc(char *str, t_data *data, int i)
{
	if (is_meta(str, i, '<') && is_meta(str, i + 1, '<')
		&& !ft_strchr("<>", str[i + 2]))
	{
		here_doc(return_word(str, i + 2), data);
		data->limiter = ft_strdup(return_word(str, i + 2));
		return (1);
	}
	return (0);
}
