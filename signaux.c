/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:47:54 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 00:39:22 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	launch_bash(char **env)
{
	int	status;
	pid_t	pid2;

	if (!isatty(0))
		exit(g_err);
	pid2 = fork();
	if (pid2 == -1)
		perror("fork");
	else if (pid2 > 0)
	{
		signal(SIGINT, intHandler);
		signal(SIGQUIT, intHandler);
		waitpid(pid2, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			launch_bash(env);
	}
	else
		while (1)
			prompt(env);
	return (g_err);
}

void intHandler(const int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n$> ", 3);
		g_err = 130;
	}
}
