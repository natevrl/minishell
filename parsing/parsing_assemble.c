/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assemble.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:15:33 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 13:24:54 by ubuntu           ###   ########.fr       */
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

void	ft_translate_token(t_list **tmp)
{
	t_list	*token;
	char	*cmd;
	int		i;

	token = *tmp;
	i = 0;
	cmd = (char *)ft_malloc(sizeof(char) * ft_strlen_token(token));
	while (token != NULL)
	{
		if (token->token == QUOTE)
			ft_assemble_quote(&token, &cmd, &i);
		else if (token->token == DQUOTE)
			ft_assemble_dquote(&token, &cmd, &i);
		else if (token->token == EXIT_CODE)
			ft_assemble_exit(&token, &cmd, &i);
		else if (token->token == DOLLARD)
			ft_assemble_dollard(&token, &cmd, &i);
		else
		{
			cmd[i] = *(char *)token->content;
			i++;
		}
		token = token->next;
	}
	cmd[i] = '\0';
	ft_fill_translated(tmp, cmd);
}

void	ft_add_token_line(t_list **cmd_token, t_list **tmp, int *pos, int *j, int *i, int token)
{
	ft_lstadd_back(cmd_token, ft_lstnew_token(ft_substr((*tmp)->cmd_translated, *pos, *j), token));
	*j = 0;
	*pos = *i + 1;
}

void	ft_assemble_token(t_list **cmd_token, t_list **tmp)
{
	t_list	*token;
	int		i;
	int		j;
	int		pos;

	i = 0;
	j = 0;
	pos = 0;
	token = *tmp;
	while (token->cmd_translated[i])
	{
		if (token->cmd_translated[i] == ';')
			ft_add_token_line(cmd_token, tmp, &pos, &j, &i, CMD);
		else if (token->cmd_translated[i] == '>' && token->cmd_translated[i + 1] == '>')
		{
			i++;
			ft_add_token_line(cmd_token, tmp, &pos, &j, &i, RD_OA);
		}
		else if (token->cmd_translated[i] == '<' && token->cmd_translated[i + 1] == '<')
		{
			i++;
			ft_add_token_line(cmd_token, tmp, &pos, &j, &i, RD_ID);
		}
		else if (token->cmd_translated[i] == '>')
			ft_add_token_line(cmd_token, tmp, &pos, &j, &i, RD_O);
		else if (token->cmd_translated[i] == '<')
			ft_add_token_line(cmd_token, tmp, &pos, &j, &i, RD_I);
		else
			j++;
		i++;
	}
	if (pos != i)
		ft_lstadd_back(cmd_token, ft_lstnew_token(ft_substr((*tmp)->cmd_translated, pos, i), CMD));
}
