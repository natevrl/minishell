/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:53:49 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/12 17:27:58 by ubuntu           ###   ########.fr       */
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

void	ft_load_env(t_list **list, char *env, char **envp)
{
	t_myenv *t;

	t = (t_myenv *)malloc(sizeof(t_myenv));
	t->name = ft_strdup(env);
	t->value = ft_strdup(env);
	t->env = ft_strdup(env);
	t->envp = envp;
	list_push(list, t);
}

void	ft_fill_basic_env(char **env, t_list **lst)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_load_env(lst, env[i], env);
		i++;
	}
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

void	ft_check_env(char **env, t_list **lst)
{
	ft_fill_basic_env(env, lst);
//	ft_check_required(my_env);
}
