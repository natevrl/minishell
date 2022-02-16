/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:38:58 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/16 05:30:16 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **argv)
{
	char	*p;

	(void)argv;
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
	exit(g_err);
}
