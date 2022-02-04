/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:54:36 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/04 19:46:51 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	exec_cmd(char *cmd)
{
	pid_t	pid = 0;
	int		status = 0;
	char *cmd_d[2] = {cmd, NULL};

	// On fork
	printf("%s\n", cmd);
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
		if (execve(cmd_d[0], cmd_d, NULL) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

void	prompt()
{
	char *read_l;
	write(1, "$> ", 3);
	while ( (read_l = readline(NULL)) )
	{
		exec_cmd(read_l);
		write(1, "$> ", 3);
		// printf("%s\n", readline);
	}
}

int	launch_bash()
{
	prompt();
	return (0);
}

int	main(void)
{
	return (launch_bash());
}
