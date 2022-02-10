/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:03:01 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 00:38:21 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(int status)
{
	g_err = statut;
	clear_memory();
	printf("error value : %d\n", g_err);
	exit(g_err);
}

void	exit_failure(const char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_exit(127);
}
