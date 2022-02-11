/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:20:43 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 22:23:04 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_print_env(t_list *lst)
{
	int	i;

	i = 0;
	while (lst->env[i])
	{
		write(1, lst->env[i], ft_strlen(lst->env[i]));
		i++;
	}
}