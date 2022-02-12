/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:31:40 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/12 10:52:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_cd(t_list *list)
{
	char	*env;

	if (list->arg[1] == NULL)
	{
		if (getenv("HOME") == NULL)
		{
			write(1, "HOME not set\n", 13);
			exit(12);
		}
		else
		{
			env = getenv("HOME");
			chdir(env);
			exit (11);
		}
	}
	else if (chdir(list->arg[1]) == -1)
	{
		write(1, "No such file or directory\n", 26);
		exit(12);
	}
	exit(10);
}
