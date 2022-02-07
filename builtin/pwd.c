/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:38:58 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/07 21:46:03 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **arg)
{
	char	*p;

	(void)arg;
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
	exit(EXIT_SUCCESS);
}
