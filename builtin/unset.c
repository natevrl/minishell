/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:23:05 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 06:56:03 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_unset(t_list **cmd)
{
	if ((*cmd)->arg[1] == NULL)
		return ;
	while ((*cmd)->env && ft_strncmp(((t_myenv *)(*cmd)->env->content)->name, (*cmd)->arg[1], ft_strlen((*cmd)->arg[1])) != 0)
		(*cmd)->env = (*cmd)->env->next;
	if ((*cmd)->env == NULL)
		return ;
	else
	{
		if ((*cmd)->env->next != NULL)
		{
			ft_update_env(((t_myenv *)(*cmd)->env->content)->envp, (*cmd)->arg[1]);
			(*cmd)->env->content = NULL;
			*(*cmd)->env = *(*cmd)->env->next;
		}
		else
		{
			ft_update_env(((t_myenv *)(*cmd)->env->content)->envp, (*cmd)->arg[1]);
			(*cmd)->env->content = NULL;
		}
		return ;
	}
}
