/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:54:36 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/07 17:23:51 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	ft_print()
// {
// 	printf("Test\n");
// }

// void	ft_load_builtin(t_list **list, t_test *built, char *name)
// {
// 	(*list)->name = name;
// 	(*list)->cmd = built;
// }

// void	ft_bultin()
// {
// 	t_list	*list;

// 	list = (t_list *)malloc(sizeof(t_list));
// 	ft_load_builtin(&list, ft_print, "ft_printf");
// //	ft_print();
// 	printf("%s\n", list->name);
// 	list->cmd();
// 	while (ft_strncmp("ft_print", list->name, 8) != 0)
// 		list = list->next;
// 	list->cmd();
// }

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

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (2);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (3);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (4);
	// if (ft_strncmp(cmd, "export", 6) == 0)
	// 	return (5);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (6);
	return (-1);
}

void	ft_pwd(void)
{
	char	*p;

	p = getcwd(NULL, 0);
	if (p != NULL)
		printf("%s\n", p);
	else
	{
		write(2, ".", 1);
		return ;
	}
	if (p)
		free(p);
}

char	*ft_echo_nathan(char **tab)
{
	int i = 1;

//	if (ft_strncmp(tab[1], "echo", 10) != 0)
//		return (NULL);
	while (tab[++i])
	{
		ft_putstr_fd(tab[i], 1);
	}
	return (NULL);
}

// char **stock_env(char **env)
// {
// 	t_list *stock;
// 	int i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		stock->next->content = env[i];
// 		i++;
// 	}
// }

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
/*		if (is_builtin(cmd->arg[0])) == -1)
		{
			printf("%s\n", arg[0]);*/
		ft_echo(cmd->arg);
		printf("test\n");
		if (execve(exec_cmd, cmd->arg, NULL) == -1)
				perror("execve failed");
		printf("testrdgdrgdrgdr\n");
/*		}
		else
		{
			printf("cest un builtin\n");
			if (is_builtin(cmd->arg[0]) == 2)
				ft_pwd();
			else if (is_builtin(cmd->arg[0]) == 1)
				ft_echo(argc, argv);
			else if (is_builtin(arg[0]) == 4)
				ft_env(env);
		}
		exit(EXIT_FAILURE);*/
	}
}

void	prompt(char **env)
{
	char	*cmd;
	(void)env;

	while (cmd)
	{
		cmd = readline("$> ");
		parse_cmd(cmd);
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
