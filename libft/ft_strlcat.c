/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:01:18 by nabentay          #+#    #+#             */
/*   Updated: 2021/08/20 10:58:21 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i2;
	size_t	i3;

	i = -1;
	i2 = ft_strlen(src);
	i3 = ft_strlen(dst);
	if (dstsize < i3 + 1)
		return (dstsize + i2);
	while (src[++i] && i3 + i < dstsize - 1)
		dst[i3 + i] = src[i];
	dst[i3 + i] = '\0';
	return (i3 + i2);
}
