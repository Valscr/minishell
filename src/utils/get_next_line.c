/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:04:18 by valentin          #+#    #+#             */
/*   Updated: 2023/02/06 12:56:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_cut_dest(char *dest)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!dest)
		return (NULL);
	while (dest[i] != '\0' && dest[i] != '\n')
		i++;
	s = malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	while (dest[j] != '\n' && dest[j] != '\0')
	{
		s[j] = dest[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*new_save(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++;
	while (str[i + j])
	{
		str[j] = str[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_next(char *save, int fd)
{
	int		bytes;
	char	*dest;

	dest = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!dest)
		return (0);
	bytes = 1;
	while (check_end(save) && bytes != 0)
	{
		bytes = read(fd, dest, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(dest);
			return (NULL);
		}
		dest[bytes] = '\0';
		save = ft_strjoin1(save, dest);
	}
	free(dest);
	return (save);
}

int	get_next_line(int fd, char **str, int last)
{
	static char	*save;

	if (last == 1)
	{
		free(save);
		return (0);
	}
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	save = get_next(save, fd);
	if (save == NULL)
		return (-1);
	*str = ft_cut_dest(save);
	save = new_save(save);
	if (!save)
		return (0);
	return (1);
}
