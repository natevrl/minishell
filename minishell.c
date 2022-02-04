/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:54:36 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/04 21:54:12 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static char	*get_cmd(char **path, char *cmd)
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

static void	exec_cmd(char **env, char *cmd)
{
	pid_t	pid = 0;
	int		status = 0;
	char *cmd_d[2] = {cmd, NULL};
	char	*path;
	char	**cmd_path;
	char	**arg;
	char	*cmd2;

	// On fork
	path = getenv("PATH");
	cmd_path = ft_split(path, ':');
	arg = ft_split(cmd, ' ');
	cmd = get_cmd(cmd_path, arg[0]);
	if (!cmd)
		exit(1);
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) {
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else {
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(cmd, arg, env) == -1)
			perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void	prompt(char **env)
{
	char *read_l;
	write(1, "$> ", 3);
	while ( (read_l = readline(NULL)) )
	{
		exec_cmd(env, read_l);
		write(1, "$> ", 3);
		// printf("%s\n", readline);
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
