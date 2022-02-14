/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:32:45 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/14 14:12:44 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing_minishell.h>

char	*ft_before_equal(char *env)
{
	char	*res;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '\0')
		return (NULL);
	res = (char *)ft_malloc(sizeof(char) * i + 1);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		res[i] = env[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_after_equal(char *env)
{
	char	*res;
	int		i;
	int		j;
	int		k;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
	{
		flag = 1;
		i++;
	}
	k = i;
	while (env[i])
	{
		i++;
		j++;
	}
	if (flag == 0)
		return (NULL);
	res = (char *)ft_malloc(sizeof(char) * j + 1);
	i = 0;
	while (env[k])
	{
		res[i] = env[k];
		i++;
		k++;
	}
	res[i] = '\0';
	return (res);
}

void	ft_update_env(char **env, char *name)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			while (env[i] && env[i + 1])
			{
				*env[i] = *env[i + 1];
				i++;
			}
			env[i] = NULL;
		}
		i++;
	}
}
