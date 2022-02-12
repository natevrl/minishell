/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:20:43 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/12 17:34:16 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_print_env(t_list *lst)
{
	while (lst->env)
	{
		write(1, ((t_myenv *)lst->env->content)->env, ft_strlen(((t_myenv *)lst->env->content)->env));
		write(1, "\n", 1);
		lst->env = lst->env->next;
	}
	exit(0);
}
