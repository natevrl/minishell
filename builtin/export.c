/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:07:46 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/27 13:34:19 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

void	add_in_envp(char **envp, char *arg)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = arg;
	envp[++i] = NULL;
}

void	add_new_envlist(t_list **list, char *arg)
{
	t_myenv	*t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_before_equal(arg);
	t->value = ft_strdup(ft_after_equal(arg));
	t->env = ft_strdup(arg);
	t->envp = ((t_myenv *)(*list)->content)->envp;
	list_push(list, t);
}

int	already_in_env(t_list **list, t_list **tmp, char *arg)
{
	char	*cmp1;
	char	*cmp2;
	char	**envp;
	t_list	*cmd;
	int		i;

	cmd = *tmp;
	envp = ((t_myenv *)(*list)->env->content)->envp;
	i = -1;
	while (envp[++i])
	{
		cmp1 = ft_before_equal(envp[i]);
		cmp2 = ft_before_equal(arg);
		if (ft_strncmp(cmp1, cmp2, ft_strlen(cmp1) + ft_strlen(cmp2)) == 0)
		{
			if (ft_strncmp(ft_after_equal(envp[i]),
					ft_after_equal(arg), ft_strlen(ft_after_equal(envp[i]))
					+ ft_strlen(ft_after_equal(arg))) != 0)
				ft_fill_env(arg, cmd, &envp[i]);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	export_error(char *arg)
{
	int		i;
	char	*before;

	if (!arg[0] || ft_isdigit(arg[0]))
		return (1);
	if (ft_strchr(arg, '='))
	{
		before = ft_before_equal(arg);
		i = -1;
		while (before[++i])
		{
			if (!ft_isalnum(before[i]) && before[i] != '_')
				return (1);
		}
	}
	return (0);
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
		if (export_error(envlist->arg[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				envlist->arg[i]);
			continue ;
		}
		if (!ft_strchr(envlist->arg[i], '='))
			continue ;
		if (already_in_env(list, &(*list)->env, envlist->arg[i]))
			continue ;
		add_in_envp(((t_myenv *)(*list)->env->content)->envp, envlist->arg[i]);
		add_new_envlist(&(*list)->env, envlist->arg[i]);
	}
}
