/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:38:58 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/03 11:57:51 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd()
{
	char	*p;

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
}

int	main()
{
	ft_pwd();
}
