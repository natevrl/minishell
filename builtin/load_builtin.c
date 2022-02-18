/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:25:21 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/18 13:11:37 by ubuntu           ###   ########.fr       */
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
	t_builtin	*t;

	t = (t_builtin *)ft_malloc(sizeof(t_builtin));
	t->name = ft_strdup(name);
	t->built = fun;
	t->built_l = ls;
	list_push(list, t);
}

void	ft_launch_builtin(t_list *list, t_list *cmd, char *name)
{
	while (ft_strncmp(((t_builtin *)list->content)->name, name,
			ft_strlen(name)) != 0)
		list = list->next;
	if (((t_builtin *)list->content)->built != NULL)
		((t_builtin *)list->content)->built(cmd->arg);
	else
		((t_builtin *)list->content)->built_l(&cmd);
}

void	ft_bultin(t_list **tmp)
{
	t_list	*list;
	t_list	*cmd;

	list = NULL;
	cmd = *tmp;
	ft_load_builtin(&list, NULL, ft_print_env, "env");
	ft_load_builtin(&list, ft_echo, NULL, "echo");
	ft_load_builtin(&list, ft_pwd, NULL, "pwd");
	while (cmd != NULL)
	{
		if (ft_strncmp("echo", cmd->arg[0], 4) == 0 && ft_strlen(cmd->arg[0]) == 4)
			ft_launch_builtin(list, cmd, "echo");
		else if (ft_strncmp("pwd", cmd->arg[0], 3) == 0 && ft_strlen(cmd->arg[0]) == 3)
			ft_launch_builtin(list, cmd, "pwd");
		else if (ft_strncmp("env", cmd->arg[0], 3) == 0 && ft_strlen(cmd->arg[0]) == 3)
			ft_launch_builtin(list, cmd, "env");
		cmd = cmd->next;
	}
}

int	ft_builtin_without_fork(t_list **tmp)
{
	t_list	*list;
	t_list	*cmd;

	list = NULL;
	cmd = *tmp;
	ft_load_builtin(&list, NULL, built_exit, "exit");
	ft_load_builtin(&list, NULL, ft_cd, "cd");
	ft_load_builtin(&list, NULL, ft_unset, "unset");
	ft_load_builtin(&list, NULL, ft_export, "export");
	if (ft_strncmp("exit", cmd->arg[0], 4) == 0 && ft_strlen(cmd->arg[0]) == 4)
	{
		ft_launch_builtin(list, cmd, "exit");
		return (1);
	}
	else if (ft_strncmp("cd", cmd->arg[0], 2) == 0 && ft_strlen(cmd->arg[0]) == 2)
	{
		ft_launch_builtin(list, cmd, "cd");
		return (1);
	}
	else if (ft_strncmp("unset", cmd->arg[0], 5) == 0 && ft_strlen(cmd->arg[0]) == 5)
	{
		ft_launch_builtin(list, cmd, "unset");
		return (1);
	}
	else if (ft_strncmp("export", cmd->arg[0], 6) == 0 && ft_strlen(cmd->arg[0]) == 6)
	{
		ft_launch_builtin(list, cmd, "export");
		return (1);
	}
	return (0);
}
