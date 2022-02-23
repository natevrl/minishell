/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assemble_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:37:05 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/23 17:37:13 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_strlen_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_fill_translated(t_list **tmp, char *cmd)
{
	t_list	*token;

	token = *tmp;
	while (token != NULL)
	{
		token->cmd_translated = cmd;
		token = token->next;
	}
}

void	ft_fill_size(t_list **tmp)
{
	t_list	*token;

	token = *tmp;
	while (token != NULL)
	{
		token->size_env = 0;
		token = token->next;
	}
}
