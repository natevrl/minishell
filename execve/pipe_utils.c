/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:27:55 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/23 19:28:20 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	number_of_pipe(t_list **token)
{
	t_list	*tmp;
	int		i;

	tmp = *token;
	i = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	finished_with_pipe(t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->token == PIPE && tmp->next == NULL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
