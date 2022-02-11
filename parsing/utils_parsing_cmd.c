/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:54 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 14:23:17 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing_minishell.h>

int	ft_strlen_token(t_list *token)
{
	int	i;

	i = 0;
	while (token->next != NULL && token->token == token->next->token)
	{
		i++;
		token = token->next;
	}
	return (i + 1);
}

t_list	*ft_lstnew_token(void	*content, int token)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->token = token;
	list->next = NULL;
	return (list);
}

void	ft_set_option(t_list **tmp)
{
	t_list	*cmd_token;

	cmd_token = *tmp;
	while (cmd_token != NULL)
	{
		if (cmd_token->token == LITERAL)
			cmd_token->arg = ft_split((char *)cmd_token->content, ' ');
		else
			cmd_token->arg = NULL;
		cmd_token = cmd_token->next;
	}
}
