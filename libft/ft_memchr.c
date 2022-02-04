/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:33:09 by nabentay          #+#    #+#             */
/*   Updated: 2021/11/24 18:19:20 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;

	if (n)
	{
		p = (unsigned char *)s;
		while (n--)
		{
			if (*p++ == (unsigned char)c)
				return ((void *)p - 1);
		}
	}
	return (NULL);
}
