/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vescaffr <vescaffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:50:15 by vescaffr          #+#    #+#             */
/*   Updated: 2022/05/04 16:33:32 by vescaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (len > (size_t)ft_strlen(s) && start <= (unsigned int)ft_strlen(s))
		len = (size_t)ft_strlen(s) - (size_t)start;
	else if (start > (unsigned int)ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s) -start)
		len = len - (size_t)start;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest || s == NULL)
		return (0);
	while (s[start] != '\0' && len > i && ft_strlen(s) > (int)start)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

/*int     main()
{
        const char s[100] = "0123456789";
        printf("%s", ft_substr(s, 9, 10));
        printf("\n");
        if (ft_substr(s, 9, 10)[strlen(ft_substr(s, 9, 10))] == '\0')
                printf("ok\n");
        printf("strlen(s)  = %lu\n", strlen(s));
        printf("strlen + 1 = %lu", strlen(ft_substr(s, 9, 10)) + 1);
	printf("\n");
}*/
