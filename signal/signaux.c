/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:47:54 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/21 19:12:50 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_pid(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid > 0 && sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_err = 130;
	}
	else
		wait(NULL);
}

int	launch_bash(t_list *cmd)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_pid;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
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
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			g_err = 131;
			ft_putstr_fd("Quit (core dumped)\n", 2);
		}
		else if (WTERMSIG(status) == SIGINT)
			g_err = 130;
		else
			g_err = 131;
	}
	else if (WIFEXITED(status))
		g_err = WEXITSTATUS(status);
}
