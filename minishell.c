/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:54:36 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/08 13:02:54 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static pid_t pid;

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

void	exec_cmd(t_list	*cmd)
{
//	pid_t	pid;
	int		status;
	char	*path_cmd;
	char	**cmd_path;
	char	*exec_cmd;

	path_cmd = getenv("PATH");
	cmd_path = ft_split(path_cmd, ':');
	exec_cmd = get_cmd(cmd_path, cmd->arg[0]);
	if (!cmd)
		exit(1);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		ft_bultin(&cmd);
		if (execve(exec_cmd, cmd->arg, NULL) == -1)
			exit_failure("command not found");
		exit(EXIT_FAILURE);
	}
}

void	prompt()
{
	char	*cmd;

	cmd = readline("$> ");	
	if (cmd[0] == '\0')
		return ;
	else if (cmd)
		parse_cmd(cmd);
}

int	launch_bash()
{
	int		status;
	
//	signal(SIGINT, intHandler);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		launch_bash();
	}
	else
		prompt();
	return (0);
}

void intHandler(int sig) 
{
	signal(sig, SIG_IGN);
	write(1, "\n", 1);
	kill(pid, SIGINT);
//	write(1, "\n$> ", 4);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	return (launch_bash(env));
}
