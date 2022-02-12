/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:47:54 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/12 17:22:58 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	launch_bash(t_list *cmd)
{
	while (1)
	{
		signal(SIGINT, intHandler);
		signal(SIGQUIT, intHandler);
		prompt(cmd);
	}
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