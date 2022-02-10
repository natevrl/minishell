/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:13:02 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/10 19:21:38 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(char **argv)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (argv[1] != NULL && strncmp(argv[1], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (argv[i])
	{
		if (argv[i])
		{
			write(1, argv[i], ft_strlen(argv[i]));
			i++;
		}
		if (argv[i] != NULL)
			write(1, " ", 1);
	}
	if (!flag)
		printf("\n");
	exit(EXIT_SUCCESS);
}
