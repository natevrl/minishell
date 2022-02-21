/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:48:53 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/21 18:18:12 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <redirection.h>

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

void	redirect_in_cmd2(t_list	*cmd, t_list *arg, int fd)
{
	pid_t	pid;
	char	*exec_cmd;

	if (ft_get_path_with_env_arg(cmd, arg, &exec_cmd) || ft_builtin_without_fork(&arg))
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
		ft_bultin(&arg);
		g_err = execve(exec_cmd, arg->arg,
				((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
}

void	here_doc(char *limiter)
{
	pid_t	pid;
	char	*tmp;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
		ft_check_signal(pid);
	else
	{
		while (1)
		{
			ft_putstr_fd("> ", 1);
			tmp = get_next_line(STDIN_FILENO);
			if (tmp == NULL)
				ft_exit(130);
			else if (ft_strncmp(tmp, limiter, ft_strlen(limiter)) == 0
				&& tmp[ft_strlen(limiter)] == '\n')
			{
				close(0);
				close(1);
				tmp = get_next_line(STDIN_FILENO);
				break ;
			}
			if (*tmp != '\n')
				ft_putstr_fd(tmp, 1);
		}
		ft_exit(0);
	}
}
