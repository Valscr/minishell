/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vescaffr <vescaffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:09:48 by vescaffr          #+#    #+#             */
/*   Updated: 2022/04/26 18:14:31 by vescaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*dst;

	i = size * count;
	dst = malloc(i);
	if (!dst || ((count > 65536) && (size > 65536)))
		return (0);
	ft_memset(dst, 0, i);
	return (dst);
}

/*int	main()
{
	ft_calloc(SIZE_MAX, SIZE_MAX);
	printf("\n");
}*/
