/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:25:21 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/07 18:27:08 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_load_builtin(t_builtin **list, t_fun *fun,char *name)
{

	(*list)->name = name;
	(*list)->built = fun;
}

void	ft_bultin(t_list *cmd)
{
	t_builtin	*list;

	(void)cmd;
	list = (t_builtin *)malloc(sizeof(t_builtin));
	ft_load_builtin(&list, ft_echo, "echo");
	ft_load_builtin(&list, ft_pwd, "pwd");
	printf("%s\n", list->name);
//	list->built(cmd->arg);
//	while (ft_strncmp("ft_print", list->name, 8) != 0)
//		list = list->next;
//	list->cmd();
}
