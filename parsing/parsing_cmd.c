/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:10 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/06 15:31:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void	ft_tokenize_input(t_token **token, char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		ft_lstadd_back_token(token, ft_lstnew_token(cmd[i]));
	while (*token != NULL)
	{
		if (ft_isalnum((*token)->c) || (*token)->c == ' ')
			(*token)->token = LITERAL;
		else if ((*token)->next != NULL && (*token)->c == '&' && (*token)->next->c == '&')
		{
			(*token)->token = AND;
			(*token)->next->token = AND;
		}
		printf("%d\n", (*token)->token);
		*token = (*token)->next;
	}
}

void	parse_cmd(char *cmd)
{
	t_token	*token;
	token = NULL;

	ft_tokenize_input(&token, cmd);
}
