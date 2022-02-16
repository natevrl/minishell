/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:32:45 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 10:46:22 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing_minishell.h>

char	*ft_before_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
	return (NULL);
}

char	*ft_after_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (str + i + 1);
	return (NULL);
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
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
		}
		i++;
	}
	i = 0;
}

size_t	ft_strlen_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_get_env_without(char *str)
{
	char	*env;
	int		i;

	i = 0;
	env = NULL;
	if (str[i] == '$')
	{
		i++;
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
			i++;
		env = ft_substr(str, 1, i - 1);
		return (env);
	}
	return (NULL);
}
