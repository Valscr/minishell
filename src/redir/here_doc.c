/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:18:31 by valentin          #+#    #+#             */
/*   Updated: 2023/02/10 20:17:32 by valentin         ###   ########.fr       */
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

int	here_doc(char *argv, t_data *data)
{
	int		file;
	char	*buf;
	pid_t	pid;
	int		status;

	status = 0;
	buf = NULL;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		free_end_process(data);
		signal(SIGINT, (void (*)(int))ctrl_c2_handler);
		file = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (file < 0)
			return (0);
		while (1)
		{	
			buf = readline("> ");
			if (buf == NULL)
			{
				ft_putstr_fd("\n", 1);
				free_str(buf);
				free_str(argv);
				close(file);
				exit (0);
			}
			if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
				break ;
			write(file, buf, ft_strlen(buf));
			write(file, "\n", 1);
			free_str(buf);
		}
		free_str(buf);
		free_str(argv);
		close(file);
		exit (0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	limiter_heredoc(char *str, t_data *data)
{
	int		i;
	int		red;
	char	*dest;

	dest = NULL;
	i = 0;
	while (str[i])
	{
		if (is_meta(str, i, '<') && is_meta(str, i + 1, '<')
			&& !ft_strchr("<>", str[i + 2]))
		{
			dest = return_word(str, i + 2);
			red = here_doc(dest, data);
			if (red == 0)
			{
				data->limiter = 1;
				return (free_str(dest), 1);
			}
			if (red == 130)
				return (free_str(dest), 2);
		}
		i++;
	}
	free_str(dest);
	return (0);
}
