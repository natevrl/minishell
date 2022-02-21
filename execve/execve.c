/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:51:11 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/21 18:56:47 by nabentay         ###   ########.fr       */
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
		ft_free (tmp);
		if (access(res, 0) == 0)
			return (res);
		ft_free (res);
		path++;
	}
	return (NULL);
}

char	*ft_find_env(t_list *lst, char	*name)
{
	while (lst)
	{
		if (ft_strncmp(name, ((t_myenv *)lst->content)->name,
				ft_strlen(name)) == 0 && ft_strlen(name)
			== ft_strlen(((t_myenv *)lst->content)->name))
			return (((t_myenv *)lst->content)->value);
		lst = lst->next;
	}
	return (NULL);
}

int	ft_get_path(t_list *cmd, char **exec_cmd)
{
	char	*path_cmd;
	char	**cmd_path;

	path_cmd = ft_find_env(cmd->env, "PATH");
	cmd_path = ft_split(path_cmd, ':');
	if (cmd->arg == NULL || cmd->arg[0] == NULL)
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
		signal(SIGQUIT, sig_handler);
		ft_bultin(&cmd);
		if (!exec_cmd)
			exit_failure(cmd->arg[0]);
		g_err = execve(exec_cmd, cmd->arg,
				((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure(cmd->arg[0]);
		ft_exit(g_err);
	}
}
