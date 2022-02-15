/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:11:46 by nabentay          #+#    #+#             */
/*   Updated: 2021/12/09 11:15:24 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_strdup(const char *str)
{
	int		i;
	int		i2;
	char	*tab;

	i = ft_strlen(str);
	i2 = -1;
	tab = malloc(sizeof(char) * i + 1);
	if (!tab)
		return (NULL);
	while (++i2 < i)
		tab[i2] = str[i2];
	tab[i2] = '\0';
	return (tab);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		j;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	tab = malloc(sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	while (s1[++i])
		tab[i] = s1[i];
	while (s2[++j])
		tab[i++] = s2[j];
	tab[i] = '\0';
	return (tab);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	len2;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	len2 = ft_strlen(s + start);
	if (len2 < len)
		len = len2;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}
