/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:54:36 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/04 19:47:27 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	prompt()
{
	write(1, "$> ", 3);
	while (1)
		printf("OK\n");
}

int	launch_bash()
{
	prompt();
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	return (launch_bash());
}
