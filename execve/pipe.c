/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:07:59 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/21 20:08:47by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_get_path_with_env(t_list *env, t_list *cmd, char **exec_cmd)
{
	char	*path_cmd;
	char	**cmd_path;

	path_cmd = ft_find_env(env->env, "PATH");
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

	path_cmd = ft_find_env(env->env, "PATH");
	cmd_path = ft_split(path_cmd, ':');
	if (cmd->arg || cmd->arg[0] == NULL)
		return (1);
	i = 0;
	while (cmd->arg[i + 1])
	{
		cmd->arg[i] = cmd->arg[i + 1];
		i++;
	}
	cmd->arg[i] = NULL;
	*exec_cmd = get_cmd(cmd_path, cmd->arg[0], path_cmd);
	return (0);
}

int	ft_get_path2(t_list **env, t_list *cmd, char **exec_cmd)
{
	char	*path_cmd;
	char	**cmd_path;
	t_list	*list;

	list = *env;
	path_cmd = ft_find_env(list->env, "PATH");
	cmd_path = ft_split(path_cmd, ':');
	if (cmd->arg[0] == NULL)
		return (1);
	*exec_cmd = get_cmd(cmd_path, cmd->arg[0], path_cmd);
	return (0);
}

void	ft_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	number_of_pipe(t_list **token)
{
	t_list	*tmp;
	int		i;

	tmp = *token;
	i = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_pipe(t_list **token, t_list **cmp)
{
	int		fd[2];
	int		pid;
	int		fd_read;
	char	*exec_tube1;
	int		i;

	fd_read = dup(0);
	i = 0;
	while ((*token) != NULL)
	{
		if (ft_get_path2(cmp, *token, &exec_tube1))
			exit_failure("invalid cmd");
		if (pipe(fd) == -1)
			exit_failure("pipe() error");
		pid = fork();
		if (pid == -1)
			exit_failure("fork() error");
		else if (pid == 0)
		{

			if (i > 0)
				dup2(fd_read, 0);
			if ((*token)->next != NULL)
				dup2(fd[1], 1);
			ft_close(fd);
			close(fd_read);
			ft_bultin(token);
			g_err = execve(exec_tube1, (*token)->arg,
					((t_myenv *)(*cmp)->env->content)->envp);
			if (g_err == -1)
				exit_failure((*token)->arg[0]);
			ft_exit(g_err);
		}
		dup2(fd[0], fd_read);
		i++;
		ft_close(fd);
		*token = (*token)->next;
	}
	i = -1;
	close(fd_read);
	while (++i <= number_of_pipe(cmp))
		wait(NULL);
}
