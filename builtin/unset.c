/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:23:05 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/14 14:12:39 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_unset(t_list **cmd)
{
	t_list	*list;

	list = *cmd;
	if (list->arg[1] == NULL)
		return ;
	while (list->env && ft_strncmp(((t_myenv *)list->env->content)->name, list->arg[1], ft_strlen(list->arg[1])) != 0)
		list->env = list->env->next;
	if (list->env == NULL)
		return ;
	else
	{
		if (list->env->next != NULL)
		{
			ft_update_env(((t_myenv *)list->env->content)->envp, list->arg[1]);
			list->env->content = NULL;
			*list->env = *list->env->next;
		}
		else
		{
			ft_update_env(((t_myenv *)list->env->content)->envp, list->arg[1]);
			list->env = NULL;
		}
		return ;
	}
}
