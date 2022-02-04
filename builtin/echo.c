/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:13:02 by nabentay          #+#    #+#             */
/*   Updated: 2022/01/22 21:31:38 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	int	flag;

	flag = 0;
	if (strncmp(argv[1], "-n", 2) == 0)
	{
		flag = 1;
		--argc;
		++argv;
	}
	--argc;
	++argv;
	while (argc > 0)
	{
		printf("%s", argv[0]);
		argc--;
		argv++;
		if (argc > 0)
			putchar(' ');
	}
	if (!flag)
		printf("\n");
	exit(EXIT_SUCCESS);
}
