/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:58:04 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/23 15:25:14 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

void	built_exit(t_list **cmd)
{
	t_list	*list;
	int		i;

	i = -1;
	list = *cmd;
	if (ft_strlen_double(list->arg) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_exit(0);
	}
	while (list->arg[1][++i])
	{
		if (ft_isalpha(list->arg[1][i]) || ft_strlen(list->arg[1]) > 20)
		{
			write(1, "numeric argument required\n", 26);
			ft_exit(2);
		}
	}
	if (ft_strlen_double(list->arg) > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		ft_exit(5);
	}
	ft_putstr_fd("exit\n", 2);
	ft_exit(ft_atoi(list->arg[1]));
}
