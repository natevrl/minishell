/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:07:46 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/16 12:58:47 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	no_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (0);
	return (1);
}

int	already_in_env(t_list **cmd, char *arg)
{
	char	*cmp2;
	t_list *envlist;

	envlist = *cmd;
	while (envlist->env)
	{
		cmp2 = ft_before_equal(arg);
		if (ft_strncmp(((t_myenv *)envlist->env->content)->name, cmp2, 100) == 0)
		{
			if (ft_strncmp(((t_myenv *)envlist->env->content)->value, ft_after_equal(arg), 100) != 0)
				((t_myenv *)envlist->env->content)->env = arg;
			return (1);
		}
		envlist->env = envlist->env->next;
	}
	return (0);
}

char	**ft_update2_env(char **env, char *newenv)
{
	char	**res;
	int	i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * ft_strlen_double(env) + 2);
	while (env[i])
	{
		res[i] = (char *)malloc(sizeof(char) * ft_strlen(env[i]));
		res[i] = env[i];
		i++;
	}
	res[i] = ft_strdup(newenv);
	res[i + 1] = NULL;
	return (res);
}

void	add_new_envlist(t_list **list, char *arg)
{
	t_myenv *t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_before_equal(arg);
	t->value = ft_strdup(ft_after_equal(arg));
	t->env = ft_strdup(arg);
	t->envp = NULL;
	list_push(&(*list)->env, t);
}

void	ft_export(t_list **list)
{
	t_list	*envlist;
	int		i;

	envlist = *list;
	if (envlist->arg[1] == NULL)
		sort_and_print_env(((t_myenv *)(*list)->env->content)->envp);
	i = 0;
	while (envlist->arg[++i])
	{
		if (no_equal(envlist->arg[i]))
			continue ;
		if (already_in_env(list, envlist->arg[i]))
			continue ;
//		((t_myenv *)(*list)->env->content)->envp = ft_update2_env(((t_myenv *)(*list)->env->content)->envp, envlist->arg[i]);
		add_new_envlist(list, envlist->arg[i]);
	}
}
