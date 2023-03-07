/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:23:25 by valentin          #+#    #+#             */
/*   Updated: 2023/03/01 23:20:56 by marvin           ###   ########.fr       */
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

# define ERROR_CTRLB 131
# define ERROR_CTRLC 130
# define ERROR_NOTFOUND 127
# define ERROR_ISDIRECTORY 126
# define ERROR_SYNTAX 2
# define ERROR_FILE 1
# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
	int			limiter2;
	int			ctrl_c;
	t_env		*env;
}				t_data;

int		add_env_variable(t_env *head, char *string);
int		add_first(t_env *list, char *string);
int		add_last(t_env *list, char *string);
int		check_arg(char *str, t_data *data);
int		check_arg2(char *str, t_data *data);
int		check_cmd(t_data *data, char *argv);
int		check_empty_line(char *buf);
int		check_error_redir(t_data *data, char *buf);
int		check_exit(char *str);
int		check_file(t_data *data, char *dest);
int		check_pipe(char *argv);
int		check_quotes(char *str, int i);
int		check_quotes1(char *str, int i, char c);
int		check_redir(char *str);
int		copy_string_array_to_env_list(t_env *head, char *string_array[]);
int		count_tab(char **str);
int		display_env_list(t_env *head);
int		end_word(char *str, int i);
int		error_slash(char *cmd_args, int type);
int		exec(t_data *data, char *argv);
int		find_char(char *str, char c);
int		find_cmd(char *str, t_data *data, int type);
int		find_cmd_after(char *str, t_data *data);
int		find_slash(char *str);
int		free_tab_str(char **str);
int		ft_cd(char **cmd_tab, t_env *env);
int		ft_echo(char **args);
int		ft_export(char *string, t_data *data);
int		ft_pwd(void);
int		ft_redir(t_data *d, char *cmd);
int		ft_unset(char *name, t_env *env);
int		get_in_out(char *argv, t_data *data, int redir);
int		get_pipes(t_data *data, char *argv);
int		here_doc(char *argv, t_data *data);
int		init(t_data *data, char **envp);
int		init_exec(char *argv, t_data *data);
int		is_cmd(char **paths, char *cmd);
int		is_file(const char *filename);
int		is_meta(char *str, int i, char c);
int		is_number(char *str);
int		is_slash(char *str);
int		iter_pipe(char *argv);
int		limiter_heredoc(char *str, t_data *data);
int		loop_pipe(t_data data, char *argv);
int		loop_shell(t_data *data);
int		open_file(char *str, t_data *data, int i, int type);
int		pars_redir_in(char *str, t_data *data);
int		pars_redir_out(char *str, t_data *data);
int		quotes_after(char const *str, int j);
int		size_list(t_env *env);
int		wait_fonct(t_data *data, char *argv);
int		write_error(char *str);
int		write_perror(char *str);
void	child(t_data *data, char *argv);
void	child_free(char **cmd_args, char *cmd);
void	close_pipes(t_data *data, int len);
void	ctrl_c_handler(int sig);
void	ctrl_c2_handler(int sig);
void	error_cmdnotfound(char *cmd_args);
void	free_end_process(t_data *data);
void	free_str(char *str);
void	get_dup2(int in, int out);
void	init_child(t_data *data, char *argv);
void	parent_free(t_data *data);
void	process_exec(t_data *data, char *argv);
void	sig_quit(int code);
void	open_here_doc(t_data *data);
void	free_t_env_list(t_env *head);
char	*cut_arg(char *str, int j, int i);
char	**check_error_redir_init(t_data *data, char *buf);
char	**env_list_to_string_array(t_env *head);
char	*find_path(t_env *head);
char	**ft_split2(char const *s, char const *sep);
char	*get_cmd(char **paths, char *cmd);
char	*get_env_list(t_env *head, char *name);
char	*get_env(char *str, t_data *data);
char	*get_env_list(t_env *head, char *name);
char	*init_shell(void);
char	*fill_replace_word(char *str3, char *str, int i, int j);
char	*new_command(char *str, t_data *data);
char	*replace_code_error(char *str, int i);
char	*replace_code_error_bis(char *str, char *dest, char *code_error, int i);
char	*replace_word(t_data *data, char *str, int i, int y);
char	*return_cmd(char *str, int i);
char	*return_cmd_after(char *str, t_data *data);
char	*return_word(char *str, int i);

extern t_sig	g_sig;

#endif