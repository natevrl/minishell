/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:13:02 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/25 23:11:16 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

void	ft_echo(char **argv)
{
	int	nflag;
	int	i;

	i = 1;
	nflag = 0;
	if (argv[1] != NULL && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		nflag = 1;
		if (ft_strlen(argv[1]) > 2 && ft_sameset(argv[1] + 2, 'n'))
			nflag = 0;
		else
			i++;
	}
	while (argv[i])
	{
		if (argv[i])
			ft_putstr_fd(argv[i], 1);
		if (argv[++i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (!nflag)
		ft_putchar_fd('\n', 1);
	ft_exit(0);
}
