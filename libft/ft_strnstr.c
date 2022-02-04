/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 22:54:32 by nabentay          #+#    #+#             */
/*   Updated: 2021/08/04 19:29:08 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		i2;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		i2 = 0;
		while (needle[i2] == haystack[i + i2] && i + i2 < len)
		{
			if (needle[i2 + 1] == '\0')
				return ((char *)haystack + i);
			i2++;
		}
		i++;
	}
	return (0);
}
