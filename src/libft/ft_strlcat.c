/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:20:46 by vescaffr          #+#    #+#             */
/*   Updated: 2022/05/25 16:47:13 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ftt_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	i;

	if (!dstsize || dstsize <= ftt_strlen(dst))
		return (dstsize + ftt_strlen(src));
	lendst = ftt_strlen(dst);
	i = 0;
	while (src[i] != '\0' && lendst + 1 < dstsize)
	{
		dst[lendst] = src[i];
		lendst++;
		i++;
	}
	dst[lendst] = '\0';
	return (ftt_strlen(dst) + ftt_strlen(&src[i]));
}

/*int     main()
{
        char dest[10] = "a";
        printf("%zd", ft_strlcat(dest, "lorem ipsum dolor sit amet", 6));
        printf("\n");
		printf("%s\n", dest);
}*/