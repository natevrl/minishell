/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:54:36 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/07 21:26:45 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*res;

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

char	*ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (NULL);
}

void	exec_cmd(t_list	*cmd, char **env)
{
	pid_t	pid;
	int		status;
	char	*path_cmd;
	char	**cmd_path;
	char	*exec_cmd;

	pid = 0;
	status = 0;
	path_cmd = getenv("PATH");
	cmd_path = ft_split(path_cmd, ':');
	exec_cmd = get_cmd(cmd_path, cmd->arg[0]);
	if (!cmd)
		exit(1);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		ft_bultin(&cmd);
		if (execve(exec_cmd, cmd->arg, env) == -1)
				perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void	prompt(char **env)
{
	char	*cmd;

	while (cmd)
	{
		cmd = readline("$> ");
		parse_cmd(cmd, env);
	}
}

int	launch_bash(char **env)
{
	prompt(env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	return (launch_bash(env));
}
