/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:07:46 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/16 09:51:21 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	add_in_envp(char **envp, char *arg)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = arg;
	envp[++i] = NULL;
}

int	already_in_env(t_list **cmd, char *arg)
{
	char	*cmp1;
	char	*cmp2;
	char	**envp;
	int		i;

	envp = ((t_myenv *)(*cmd)->env->content)->envp;
	i = -1;
	while (envp[++i])
	{
		cmp1 = ft_before_equal(envp[i]);
		cmp2 = ft_before_equal(arg);
		if (ft_strncmp(cmp1, cmp2, 100) == 0)
		{
			if (ft_strncmp(ft_after_equal(envp[i]), after_equal(arg), 100) != 0)
				envp[i] = arg;
			return (1);
		}
	}
	return (0);
}

int	export_error(char *arg)
{
	int		i;
	char	*before;

	before = ft_before_equal(arg);
	i = -1;
	if (ft_isdigit(arg[0]))
		return (1);
	while (before[++i])
	{
		if (!ft_isalnum(before[i]))
			return (1);
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
		if (no_equal(envlist->arg[i]))
			continue ;
		if (export_error(envlist->arg[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				envlist->arg[i]);
			continue ;
		}
		if (already_in_env(&envlist, envlist->arg[i]))
			continue ;
		add_in_envp(((t_myenv *)(*list)->env->content)->envp, envlist->arg[i]);
	}
}*/
