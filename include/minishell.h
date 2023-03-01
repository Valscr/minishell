/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:23:25 by valentin          #+#    #+#             */
/*   Updated: 2023/03/01 17:42:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_sig
{
	int			code_error;
}				t_sig;

typedef struct s_data
{
	pid_t		pid;
	int			*tube;
	int			type;
	int			infile;
	int			outfile;
	int			count;
	int			redir;
	int			error;
	char		*paths;
	char		*argv;
	char		**envp;
	char		*cmd_redir;
	char		**cmd_paths;
	char		**cmd;
	char		**cmd_tab;
	int			limiter;
	int			file;
	int			ctrl_c;
	t_env		*env;
}				t_data;

int		init(t_data	*data, char **envp);
char	*find_path(t_env *head);
void	ctrl_c_handler(int sig);
void	ctrl_c2_handler(int sig);
void	sig_quit(int code);
int		shell(t_data *data);
int		write_perror(char *str);
int		write_error(char *str);
int		ft_cd(char **cmd_tab, t_env *env);
int		ft_unset(char *name, t_env *env);
int		ft_echo(char **args);
int		ft_pwd(void);
void	child_free(char **cmd_args, char *cmd);
char	*get_cmd(char **paths, char *cmd);
int		find_cmd(char *str, t_data *data, int type);
int		find_char(char *str, char c);
int		check_redir(char *str);
int		ft_redir(t_data *d, char *cmd);
char	**ft_split2(char const *s, char const *sep);
int		count_tab(char **str);
int		check_quotes(char *str, int i);
int		check_quotes1(char *str, int i, char c);
int		quotes_after(char const *str, int j);
int		ft_export(char *string, t_data *data);
char	*replace_word(t_data *data, char *str, int i);
char	*new_command(char *str, t_data *data);
char	*return_cmd(char *str, int i);
int		pars_redir_in(char *str, t_data *data);
int		here_doc(char *argv, t_data *data);
int		is_meta(char *str, int i, char c);
int		limiter_heredoc(char *str, t_data *data);
int		pars_redir_out(char *str, t_data *data);
int		get_in_out(char *argv, t_data *data, int redir);
int		is_cmd(char **paths, char *cmd);
int		is_file(const char *filename);
int		exec(t_data *data, char *argv);
void	child(t_data *data, char *argv);
int		loop_pipe(t_data data, char *argv);
int		loop_shell(t_data *data);
int		open_file(char *str, t_data *data, int i, int type);
int		check_arg(char *str, t_data *data);
int		check_arg2(char *str, t_data *data);
char	*cut_arg(char *str, int j, int i);
char	*return_word(char *str, int i);
int		end_word(char *str, int i);
int		get_pipes(t_data *data, char *argv);
void	get_dup2(int in, int out);
void	parent_free(t_data *data);
void	close_pipes(t_data *data, int len);
int		iter_pipe(char *argv);
int		free_tab_str(char **str);
void	free_str(char *str);
void	free_all(t_data *data);
int		add_env_variable(t_env *head, char *string);
int		copy_string_array_to_env_list(t_env *head, char *string_array[]);
char	**env_list_to_string_array(t_env *head);
char	*get_env_list(t_env *head, char *name);
void	display_env_list(t_env **head);
char	*get_env(char *str, t_data *data);
int		wait_fonct(t_data *data, char *argv);
char	*replace_code_error(char *str, int i);
int		check_file(t_data *data, char *dest);
char	*return_cmd_after(char *str, t_data *data);
int		find_cmd_after(char *str, t_data *data);
void	open_here_doc(t_data *data);
void	free_t_env_list(t_env *head);
void	free_end_process(t_data *data);
int		check_exit(char *str);
int		is_number(char	*str);
int		check_empty_line(char *buf);
char	*init_shell(void);
int		find_slash(char *str);
int		is_slash(char *str);
void	init_child(t_data *data, char *argv);
int		error_slash(char **cmd_args, int type);
void	error_cmdnotfound(char **cmd_args);
int		init_exec(char *argv, t_data *data);
int		check_pipe(char *argv);
int		check_error_redir(t_data *data, char *buf);
int		check_cmd(t_data *data, char *argv);
int		add_first(t_env *list, char *string);
int		add_last(t_env *list, char *string);
int		size_list(t_env *env);
void	process_exec(t_data *data, char *argv);

extern t_sig	g_sig;

#endif