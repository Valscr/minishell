/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vescaffr <vescaffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:42:05 by vescaffr          #+#    #+#             */
/*   Updated: 2022/05/16 13:51:38 by vescaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int nb, int power)
{
	int	i;
	int	res;

	if (power < 0)
		return (0);
	i = 0;
	res = 1;
	while (i++ < power)
		res *= nb;
	return (res);
}

int	ft_destsize(int n)
{
	unsigned int	nb;
	int				size;

	size = 1;
	if (n < 0)
	{
		size++;
		nb = (unsigned int)(n * -1);
	}
	else
		nb = (unsigned int)n;
	while (nb >= 10)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

static char	*ft_filldest(unsigned int nb, char *dest, int i, int size)
{
	while (size > 0)
	{
		dest[i++] = nb / ft_pow(10, size) + '0';
		nb = nb - (nb / ft_pow(10, size) * ft_pow(10, size));
		size--;
	}
	dest[i] = nb + '0';
	dest[++i] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	char			*dest;
	unsigned int	nb;
	int				size;
	int				i;

	i = 0;
	size = ft_destsize(n);
	dest = malloc(sizeof(char) * (size-- + 1));
	if (!dest)
		return (0);
	if (n < 0)
	{
		dest[i++] = '-';
		size--;
		nb = (unsigned int)(n * -1);
	}
	else
		nb = (unsigned int)n;
	dest = ft_filldest(nb, dest, i, size);
	return (dest);
}

/*int	main()
{
	int	n;
	int 	i;
	int	size;
	int	j;
	int	d;

	size = 1;
	i = 0;
	n = 1234567;
	d = n;
	if (n == -2147483648)
		n += 1;
	if (n < 0)
	{
		j = n * -1;
		size++;
	}
	else 
		j = n;
	while (j >= 10)
        {
                j = j / 10;
                size++;
        }
	if (d == -2147483648)
		n -= 1;
	while (i < size)
	{
		printf("%c", ft_itoa(n)[i]);
		i++;
	}
	printf("\n");
	if (ft_itoa(n)[i] == '\0')
	{
		printf("nombre de caracteres : %d + le 0\n", i);
		printf("dernier caractere est egale à 0 : ok\n");
	}
}*/
