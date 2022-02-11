/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:25:21 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 23:06:26 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	list_push(t_list **lst_addr, void *data)
{
	t_list	**ptr;

	ptr = lst_addr;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = ft_malloc(sizeof(**ptr));
	(*ptr)->content = data;
	(*ptr)->next = NULL;
}

void	ft_load_builtin(t_list **list, t_fun *fun, t_ls *ls, char *name)
{
	t_builtin *t;

	t = (t_builtin *)malloc(sizeof(t_builtin));
	t->name = ft_strdup(name);
	t->built = fun;
	t->built_l = ls;
	list_push(list, t);
}

void	ft_bultin(t_list **tmp)
{
	t_list	*list;
	t_list	*cmd;
	list = NULL;

	cmd = *tmp;
	ft_load_builtin(&list, NULL, ft_cd, "cd");
	ft_load_builtin(&list, NULL, ft_print_env, "env");
	ft_load_builtin(&list, ft_echo, NULL, "echo");
	ft_load_builtin(&list, ft_pwd, NULL, "pwd");
	while (cmd != NULL)
	{
		if (ft_strncmp("echo", cmd->arg[0], 4) == 0)
		{
			if (ft_strncmp(((t_builtin *)list->content)->name, "echo", 4) == 0)
				((t_builtin *)list->content)->built(cmd->arg);
			else
				list = list->next;
		}
		else if (ft_strncmp("pwd", cmd->arg[0], 4) == 0)
		{
			if (ft_strncmp(((t_builtin *)list->content)->name, "pwd", 4) == 0)
				((t_builtin *)list->content)->built(cmd->arg);
			else
				list = list->next;
		}
		else if (ft_strncmp("env", cmd->arg[0], 3) == 0)
		{
			if (ft_strncmp(((t_builtin *)list->content)->name, "env", 3) == 0)
				((t_builtin *)list->content)->built_l(cmd);
			else
				list = list->next;
		}
		else if (ft_strncmp("cd", cmd->arg[0], 2) == 0)
		{
			if (ft_strncmp(((t_builtin *)list->content)->name, "cd", 2) == 0)
				((t_builtin *)list->content)->built_l(cmd);
			else
				list = list->next;
		}
		cmd = cmd->next;
	}
}
