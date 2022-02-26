/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:03:01 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/26 00:03:30 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(int status)
{
	g_err = status;
	clear_memory();
	exit(g_err);
}

void	exit_failure(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, ": Command not found", 19);
	write(2, "\n", 1);
	ft_exit(127);
}

void	err_found_msg(char *s, int flag)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	if (flag)
		ft_exit(127);
}
