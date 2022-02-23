/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:38:58 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/23 23:34:32 by ubuntu           ###   ########.fr       */
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
