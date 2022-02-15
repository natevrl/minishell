/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:48:53 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/14 18:46:11y ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_out_cmd(t_list	*cmd, int fd)
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
		dup2(fd, STDOUT_FILENO);
		close(fd);
		ft_bultin(&cmd);
		g_err = execve(exec_cmd, cmd->arg, ((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
}

void	redirect_in_cmd(t_list	*cmd, int fd)
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
		dup2(fd, STDIN_FILENO);
		close(fd);
		ft_bultin(&cmd);
		g_err = execve(exec_cmd, cmd->arg, ((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
}

void	here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		printf("error\n");
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while ((line = get_next_line(fd[1])))
		{
			printf("OK\n");
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
