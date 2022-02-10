/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:03:01 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/10 22:03:08 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(int status)
{
	if (status == EXIT_FAILURE)
		g_err = 127;
	clear_memory();
	printf("error value : %d\n", g_err);
	exit(g_err);
}

void	exit_failure(const char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_exit(EXIT_FAILURE);
}
