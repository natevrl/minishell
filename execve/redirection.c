/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:48:53 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/17 14:24:57 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_out_cmd(t_list	*cmd, int fd)
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
		dup2(fd, STDOUT_FILENO);
		close(fd);
		ft_bultin(&cmd);
		g_err = execve(exec_cmd, cmd->arg,
				((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
}

void	redirect_in_cmd(t_list	*cmd, int fd)
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
		dup2(fd, STDIN_FILENO);
		close(fd);
		ft_bultin(&cmd);
		g_err = execve(exec_cmd, cmd->arg,
				((t_myenv *)cmd->env->content)->envp);
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
