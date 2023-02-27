/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:14:13 by valentin          #+#    #+#             */
/*   Updated: 2023/02/27 00:45:11 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(char **cmd_tab)
{
	char	cwd[PATH_MAX];
	char	*str;	

	if (!cmd_tab[1])
	{
		chdir("/");
		return (0);
	}
	if (chdir(cmd_tab[1]) == -1)
	{
		str = ft_strjoin(getcwd(cwd, PATH_MAX), "/");
		str = ft_strjoin(str, cmd_tab[1]);
		if (chdir(str) != 0)
			return (perror(cmd_tab[1]), 1);
		free(str);
		return (0);
	}
	return (0);
}
