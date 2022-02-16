/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:20:43 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 10:53:19 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_env(t_list **cmd)
{
	t_list	*list;

	list = *cmd;
	while (list->env)
	{
		write(1, ((t_myenv *)list->env->content)->env,
			ft_strlen(((t_myenv *)list->env->content)->env));
		write(1, "\n", 1);
		list->env = list->env->next;
	}
	exit(0);
}
