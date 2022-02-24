/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assemble_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:37:05 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/24 14:13:44 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	while (token)
	{
		token->env = env;
		token = token->next;
	}
}

void	ft_last_step(t_list **cmd_token, t_list **tmp, t_list *token, int i)
{
	if (token != NULL)
		i++;
	if (*ft_split(ft_substr((*tmp)->cmd_translated, (*tmp)->pos, i), ' ')
		== NULL)
		return ;
	else if ((*tmp)->pos != i)
		ft_lstadd_back(cmd_token, ft_lstnew_token
			(ft_substr((*tmp)->cmd_translated, (*tmp)->pos, i), CMD));
}
