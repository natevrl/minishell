/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:23:05 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 07:28:29:48nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset_env(t_list **cmd, int i)
{
	while ((*cmd)->env->next
		&& ft_strncmp(((t_myenv *)(*cmd)->env->next->content)->name,
		(*cmd)->arg[i], ft_strlen((*cmd)->arg[i])
		+ ft_strlen(((t_myenv *)(*cmd)->env->next->content)->name)) != 0)
		(*cmd)->env = (*cmd)->env->next;
	if ((*cmd)->env->next == NULL)
		return ;
	else
	{
		if ((*cmd)->env->next->next != NULL)
			(*cmd)->env->next = (*cmd)->env->next->next;
		else
			(*cmd)->env->next = NULL;
		ft_update_env(((t_myenv *)(*cmd)->env->content)->envp, (*cmd)->arg[i]);
	}
}

int	ft_check_unset(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[i])
		{
			if (ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i]))
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	ft_unset(t_list **cmd)
{
	int	i;

	i = 0;
	while ((*cmd)->arg[++i])
	{
		if (ft_check_unset((*cmd)->arg[i]))
			unset_env(cmd, i);
		else
			ft_putstr_fd("not a valid identifier\n", 2);
	}
	return ;
}
