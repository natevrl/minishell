/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:31:40 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/21 18:16:40 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

void	ft_cd(t_list **cmd)
{
	t_list	*list;
	char	*env;

	list = *cmd;
	if (list->arg[1] == NULL)
	{
		if (getenv("HOME") == NULL)
			write(1, "HOME not set\n", 13);
		else
		{
			env = getenv("HOME");
			chdir(env);
		}
	}
	else if (chdir(list->arg[1]) == -1)
		write(1, "No such file or directory\n", 26);
}
