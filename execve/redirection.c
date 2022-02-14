/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:48:53 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/14 13:39:04 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_out_cmd(t_list	*cmd)
{
	pid_t	pid;
	int		status;
	char	*path_cmd;
	char	**cmd_path;
	char	*exec_cmd;
	int		fd;

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
		fd = creat(cmd->next->arg[0], 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		ft_bultin(&cmd);
		g_err = execve(exec_cmd, cmd->arg, ((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
}

void	redirect_in_cmd(t_list	*cmd)
{
	pid_t	pid;
	int		status;
	char	*path_cmd;
	char	**cmd_path;
	char	*exec_cmd;
	int		fd;

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
		fd = open(cmd->next->arg[0], O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		ft_bultin(&cmd);
		g_err = execve(exec_cmd, cmd->arg, ((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
}
