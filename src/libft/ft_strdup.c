/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:23:09 by vescaffr          #+#    #+#             */
/*   Updated: 2023/02/28 14:19:29 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		size;

	if (s1 == NULL)
		return (0);
	size = ft_strlen(s1) + 1;
	dest = malloc(sizeof(char) * size);
	if (!dest)
		return (0);
	ft_memcpy(dest, s1, size);
	return (dest);
}
