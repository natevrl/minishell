/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_basic_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:32:28 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/22 18:54:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env_minishell.h>

void	ft_add_under(char **envp, t_list **list)
{
	t_myenv	*t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_strdup("_");
	t->value = ft_strdup("/usr/bin/env");
	t->env = ft_strdup("_=/usr/bin/env");
	t->envp = envp;
	list_push(list, t);
}

void	ft_add_pwd(char **envp, t_list **list)
{
	t_myenv	*t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_strdup("PWD");
	t->value = ft_strdup("/");
	t->env = ft_strdup("PWD=/");
	t->envp = envp;
	list_push(list, t);
}

void	ft_add_shlvl(char **envp, t_list **list)
{
	t_myenv	*t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_strdup("SHLVL");
	t->value = ft_strdup("1");
	t->env = ft_strdup("SHLVL=1");
	t->envp = envp;
	list_push(list, t);
}

void	ft_check_required(char **envp, t_list **lst)
{
	if (*lst)
	{
		if (ft_strncmp("_", ((t_myenv *)(*lst)->content)->name, 1) != 0)
			ft_find_add_env(envp, lst, "_");
		if (ft_strncmp("SHLVL", ((t_myenv *)(*lst)->content)->name, 5) != 0)
			ft_find_add_env(envp, lst, "SHLVL");
		if (ft_strncmp("PWD", ((t_myenv *)(*lst)->content)->name, 3) != 0)
			ft_find_add_env(envp, lst, "PWD");
	}
	else
	{
		ft_add_pwd(envp, lst);
		ft_add_shlvl(envp, lst);
		ft_add_under(envp, lst);
	}
}
