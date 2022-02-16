/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:58:04 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 05:23:39 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_exit(t_list **cmd)
{
	t_list	*list;
	int		i;

	i = 0;
	list = *cmd;
	while (list->arg[i])
		i++;
	if (i == 1)
		exit(2);
	i = 0;
	while (list->arg[1][i])
	{
		if (ft_isalpha(list->arg[1][i]))
		{
			write(1, "numeric argument required\n", 26);
			exit(2);
		}
		i++;
	}
	i = 0;
	while (list->arg[i])
		i++;
	if (i > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		exit(5);
	}
	g_err = ft_atoi(list->arg[1]);
	exit(g_err);
}
