/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:47:54 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 11:02:58 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	launch_bash(t_list *cmd)
{
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		prompt(cmd);
	}
	return (g_err);
}

void	sig_handler(const int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_err = 130;
	}
}

void	ft_check_signal(int pid)
{
	int	status;

	signal(SIGQUIT, sig_handler);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_err = 131;
	}
	else
		g_err = WEXITSTATUS(status);
}
