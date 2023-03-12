/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:48:13 by valentin          #+#    #+#             */
/*   Updated: 2023/03/12 20:34:06 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len)
		{
			if (ft_strncmp(tab[i], tab[i + 1], ft_strlen(tab[i])) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	print_sorted_env(t_env *env)
{
	int		i;
	char	**env_tab;

	env_tab = env_list_to_string_array(env);
	sort_env(env_tab, count_tab(env_tab));
	i = 0;
	while (env_tab[i + 1])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env_tab[i], 1);
		i++;
	}
	free_tab_str(env_tab);
}

int	ft_export(char *string, t_data *data)
{
	printf("string = %s\n", string);
	add_env_variable(data->env, string);
	return (0);
}
