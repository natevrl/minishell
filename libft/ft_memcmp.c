/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 22:38:23 by nabentay          #+#    #+#             */
/*   Updated: 2021/11/24 18:19:37 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n)
	{
		n += 1;
		while (--n)
		{
			if (*(unsigned char *)s1++ != *(unsigned char *)s2++)
				return (*(unsigned char *)--s1 - *(unsigned char *)--s2);
		}
	}
	return (0);
}
