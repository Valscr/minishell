/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:22:17 by valentin          #+#    #+#             */
/*   Updated: 2023/03/09 23:32:25 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_char(char *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (check_quotes(str, i))
				j++;
		}
		i++;
	}
	return (j);
}

int	check_redir(char *str)
{
	if (ft_strnstr(str, "<", ft_strlen(str)) && find_char(str, '<'))
		return (1);
	if (ft_strnstr(str, ">", ft_strlen(str)) && find_char(str, '>'))
		return (1);
	if (ft_strnstr(str, "<<", ft_strlen(str)) && find_char(str, '<'))
		return (1);
	if (ft_strnstr(str, ">>", ft_strlen(str)) && find_char(str, '>'))
		return (1);
	return (0);
}

int	end_word(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] != ' ' && str[i] && str[i] != '>' && str[i] != '<'
		&& str[i] != '"' && str[i] != '\'' && str[i] != '\0')
		i++;
	return (i);
}
