/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assemble_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:37:05 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/23 23:25:59 by ubuntu           ###   ########.fr       */
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

void	set_token(t_list **token, int t)
{
	(*token)->token = t;
	(*token)->next->token = t;
}

void	ft_fill_list_env(t_list **tmp, t_list *env)
{
	t_list	*token;

	token = *tmp;
	while(token)
	{
		token->env = env;
		token = token->next;
	}
}
