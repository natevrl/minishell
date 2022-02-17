/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:07:59 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/17 16:29:44 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_get_path_with_env(t_list *env, t_list *cmd, char **exec_cmd)
{
	char	*path_cmd;
	char	**cmd_path;

	path_cmd = ft_find_path(env->env);
	cmd_path = ft_split(path_cmd, ':');
	if (cmd->arg[0] == NULL)
		return (1);
	*exec_cmd = get_cmd(cmd_path, cmd->arg[0], path_cmd);
	return (0);
}

int	ft_get_path_with_env_arg(t_list *env, t_list *cmd, char **exec_cmd)
{
	char	*path_cmd;
	char	**cmd_path;
	int		i;

	path_cmd = ft_find_path(env->env);
	cmd_path = ft_split(path_cmd, ':');
	if (cmd->arg[0] == NULL)
		return (1);
	i = 0;
	while (cmd->arg[i + 1])
	{
		cmd->arg[i] = cmd->arg[i + 1];
		i++;
	}
	cmd->arg[i] = '\0';
	*exec_cmd = get_cmd(cmd_path, cmd->arg[0], path_cmd);
	return (0);
}

void	ft_pipe(t_list **token)
{
	int fd[2]; // fd[0] = read (STDIN) // fd[1] = write (STDOUT)
	int pid1;
	int pid2;
	char *exec_tube1;
	char *exec_tube2;

	if (ft_get_path_with_env(*token, *token, &exec_tube1))
		return ;
	if (ft_get_path_with_env(*token, (*token)->next, &exec_tube2))
		return ;
	if (pipe(fd) == -1)
		return ;
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork() error");
		return ;
	}
	else if (pid1 == 0)
	{	// enfant qui legue son process a execve(ping)
		close(fd[0]); // non utilise
		dup2(fd[1], STDOUT_FILENO); // STDIN de pipe va prendre STDOUT de ping
		close(fd[1]); // pointe sur le meme pipe que dup2 (dup2 ne copie pas seulement, il duplique);
		execve(exec_tube1, (*token)->arg, ((t_myenv *)(*token)->env->content)->envp);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork() error");
		return ;
	}
	else if (pid2 == 0)
	{ // process enfant 2 (grep)
		close(fd[1]); // pointe sur le meme pipe que dup2 (dup2 ne copie pas seulement, il duplique);
		dup2(fd[0], STDIN_FILENO); // STDIN de grep atend STDOUT du pipe (qui est le STDOUT de ping a la base)
		close(fd[0]); // non utilise
		execve(exec_tube2, (*token)->next->arg, ((t_myenv *)(*token)->env->content)->envp);
	}
	close(fd[0]);
	close(fd[1]);
	ft_check_signal(pid1);
	ft_check_signal(pid2);
	*token = (*token)->next;
}
