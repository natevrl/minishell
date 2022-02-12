/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:54:36 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/12 11:14:45 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*res;

	if (cmd[0] == '/' || cmd[0] == '.')
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
	if (path_cmd)
		exec_cmd = get_cmd(cmd_path, cmd->arg[0]);
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
			g_err = 131;
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 10)
			chdir(cmd->arg[1]);
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 11)
			chdir(getenv("HOME"));
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 12)
			g_err = 1;
		else
			g_err = WEXITSTATUS(status);
	}
	else
	{
		ft_bultin(&cmd);
		if (!path_cmd)
			exit_failure("command not found");
		g_err = execve(exec_cmd, cmd->arg, cmd->env);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
}

void	prompt(char **env)
{
	char	*cmd;

	cmd = readline("$> ");
	if (!cmd)
	{
		write(1, "exit\n", 5);
		ft_exit(g_err);
	}
	add_history(cmd);
	if (*cmd == '\0')
		return ;
	parse_cmd(cmd, env);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_err = 0;

	return (launch_bash(env));
}
