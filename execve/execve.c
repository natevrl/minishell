/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:51:11 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/14 14:08:52 by ubuntu           ###   ########.fr       */
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

void	exec_cmd(t_list	*cmd)
{
	pid_t	pid;
	int		status;
	char	*path_cmd;
	char	**cmd_path;
	char	*exec_cmd;

	path_cmd = getenv("PATH");
	cmd_path = ft_split(path_cmd, ':');
	if (cmd->arg[0] == NULL)
		return ;
	exec_cmd = get_cmd(cmd_path, cmd->arg[0], path_cmd);
	if (ft_builtin_without_fork(&cmd) == 1)
		return ;
	if (!cmd)
		ft_exit(127);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		signal(SIGQUIT, intHandler);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			g_err = 127;
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			g_err = 131;
		}
		else
			g_err = WEXITSTATUS(status);
	}
	else
	{
		ft_bultin(&cmd);
		g_err = execve(exec_cmd, cmd->arg, ((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
}
