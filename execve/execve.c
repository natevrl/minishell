/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:51:11 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 11:02:48 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_absolute(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/' || cmd[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

char	*get_cmd(char **path, char *cmd, char *path_cmd)
{
	char	*tmp;
	char	*res;

	if (ft_absolute(cmd) || !path_cmd)
		return (cmd);
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		res = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(res, 0) == 0)
			return (res);
		free (res);
		path++;
	}
	return (NULL);
}

char	*ft_find_path(t_list *lst)
{
	while (lst)
	{
		if (ft_strncmp("PATH", ((t_myenv *)lst->content)->name, 4) == 0)
			return (((t_myenv *)lst->content)->value);
		lst = lst->next;
	}
	return (NULL);
}

int	ft_get_path(t_list *cmd, char **exec_cmd)
{
	char	*path_cmd;
	char	**cmd_path;

	path_cmd = ft_find_path(cmd->env);
	cmd_path = ft_split(path_cmd, ':');
	if (cmd->arg[0] == NULL)
		return (1);
	*exec_cmd = get_cmd(cmd_path, cmd->arg[0], path_cmd);
	return (0);
}

void	exec_cmd(t_list	*cmd)
{
	pid_t	pid;
	char	*exec_cmd;

	if (ft_get_path(cmd, &exec_cmd) || ft_builtin_without_fork(&cmd))
		return ;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
		ft_check_signal(pid);
	else
	{
		ft_bultin(&cmd);
		g_err = execve(exec_cmd, cmd->arg,
				((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure(cmd->arg[0]);
		ft_exit(g_err);
	}
}
