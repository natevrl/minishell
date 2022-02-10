/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:53:49 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/10 21:35:46 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_display_env(char *env)
{
	char	*res;

	res = getenv(env);
	if (res)
		write(1, res, ft_strlen(res));
}

char	*ft_get_env(char *sign, int pos)
{
	char	*env;
	int		j;

	j = 0;
	env = NULL;
	while (sign[pos])
	{
		if (sign[pos] == '$')
		{
			pos++;
			while (sign[pos] != '\0' && sign[pos] != ' ' && sign[pos] != '$')
			{
				pos++;
				j++;
			}
			if (sign[pos] != '$')
			{
				env = ft_substr(sign, pos - j, j);
				return (getenv(env));
			}
			else
			{
				env = ft_substr(sign, pos - j, j);
				ft_get_env(sign, pos);
				return (ft_get_env(sign, pos));
			}
		}
		pos++;
	}
	return (NULL);
}

int	ft_show_env(char *str)
{
	if (ft_get_env(str, 0) == 0)
		return (1);
	return (0);
}
