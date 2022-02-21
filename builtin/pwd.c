/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:38:58 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/21 18:17:24 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

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
	ft_exit(0);
}
