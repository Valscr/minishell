/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:18:31 by valentin          #+#    #+#             */
/*   Updated: 2023/03/11 23:53:47 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_here_doc(t_data *data)
{
	data->infile = open(".heredoc_tmp", O_CLOEXEC | O_RDONLY);
	if (data->infile < 0)
		unlink(".heredoc_tmp");
	return ;
}

int	here_doc_init(t_data *data)
{
	int		file;

	free_end_process(data);
	signal(SIGINT, (void (*)(int))ctrl_c2_handler);
	file = open(".heredoc_tmp", O_CLOEXEC | O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file < 0)
		return (0);
	return (file);
}

void	exec_here_doc(t_data *data, int file, char *buf, char *argv)
{
	file = here_doc_init(data);
	while (1)
	{	
		buf = readline("> ");
		if (buf == NULL)
		{
			ft_putstr_fd("\n", 1);
			free_str(buf);
			free_str(argv);
			close(file);
			exit (g_sig.code_error);
		}
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
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

int	here_doc(char *argv, t_data *data)
{
	int		file;
	char	*buf;
	pid_t	pid;
	int		status;

	status = 0;
	buf = NULL;
	file = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exec_here_doc(data, file, buf, argv);
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

	i = -1;
	dest = NULL;
	while (str[++i])
	{
		if (is_meta(str, i, '<') && is_meta(str, i + 1, '<')
			&& (!ft_strchr("<>", str[i + 2]) || str[i + 2] == '\0'))
		{
			if (str[i + 2] == '\0')
				return (0);
			dest = return_word(str, i + 2);
			if (!dest)
				return (0);
			red = here_doc(dest, data);
			if (red == 0)
			{
				data->limiter = 1;
				return (free_str(dest), 1);
			}
			if (red == 130)
				return (free_str(dest), 2);
		}
	}
	return (free_str(dest), 0);
}
