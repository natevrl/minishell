/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:54 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/18 14:03:22 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing_minishell.h>

int	ft_strlen_token(t_list *token)
{
	int		i;

	i = 0;
	while (token != NULL)
	{
//		printf("%d\n", token->token);
		if (token->token == EXIT_CODE)
			i += ft_strlen(ft_itoa(g_err));
		else if (token->token == DQUOTE || token->token == QUOTE)
			i -= 1;
		else if (token->token == DOLLARD)
		{
			i++;
			if (getenv(ft_get_env_without((char *)token->content)) != NULL)
				i += ft_strlen(getenv(ft_get_env_without(
								(char *)token->content)));
		}
		i++;
		token = token->next;
	}
	return (i + 1);
}

t_list	*ft_lstnew_token(void	*content, int token)
{
	t_list	*list;

	list = ft_malloc(sizeof(t_list));
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
		if (cmd_token->token == CMD || cmd_token->token == RD_O
			|| cmd_token->token == RD_I
			|| cmd_token->token == RD_OA || cmd_token->token == RD_ID || cmd_token->token == PIPE)
			cmd_token->arg = ft_split((char *)cmd_token->content, ' ');
		else
			cmd_token->arg = NULL;
		cmd_token = cmd_token->next;
	}
}
