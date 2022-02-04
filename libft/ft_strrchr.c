/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:53:01 by nabentay          #+#    #+#             */
/*   Updated: 2021/11/23 05:50:30 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	int		i;

	i = 0;
	while (*s)
	{
		if (*s == (char)c)
		{
			res = (char *)s;
			i++;
		}
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else if (i == 0)
		return (NULL);
	return (res);
}
