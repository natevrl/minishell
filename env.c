/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:53:49 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/12 12:31:55 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*ft_get_env(char *str, t_list **list)
{
	char	*env;
	int		i;

	i = 0;
	env = NULL;
	if (str[i] == '$')
	{
		i++;
		while (str[i] != '\0' && str[i] != ' '  && str[i] != '$' && str[i] != '\"')
		{
			i++;
			*list = (*list)->next;
		}
		env = ft_substr(str, 1, i - 1);
		return (env);
	}
	return (NULL);
}

size_t	ft_strlen_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_load_env(t_list **list, char *env)
{
	t_myenv *t;

	t = (t_myenv *)malloc(sizeof(t_myenv));
	t->name = ft_strdup(name);
	t->value = ft_strdup(name);
	t->env = ft_strdup(name);
	list_push(list, t);
}

char	**ft_fill_basic_env(char **env)
{
	t_list *my_env;
	int		i;

	i = 0;
	list = NULL;
	while (env[i])
	{
		ft_load_env(&list, env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

/*void	ft_check_required(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) != 0)
		{
		}


		i++;
	}
}*/

char	**ft_check_env(char **env)
{
	char **my_env;

	my_env = ft_fill_basic_env(env);
//	ft_check_required(my_env);
	return (my_env);
}
