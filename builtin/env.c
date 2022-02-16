/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:20:43 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 06:55:47 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_env(t_list **cmd)
{
	t_list	*list;

	list = *cmd;
	while (list->env)
	{
		ft_putstr_fd(((t_myenv *)list->env->content)->env, 1);
		write(1, "\n", 1);
		list->env = list->env->next;
	}
	exit(0);
}
