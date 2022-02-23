/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assemble.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:15:33 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/23 19:51:48 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_token_associated(t_list **token, char **cmd, int *i, t_list *lst)
{
	if ((*token)->token == QUOTE)
	{
		if (ft_assemble_quote(token, cmd, i))
			return (2);
	}
	else if ((*token)->token == DQUOTE)
	{
		if (ft_assemble_dquote(token, cmd, i, lst))
			return (2);
	}
	else if ((*token)->token == EXIT_CODE)
		ft_assemble_exit(token, cmd, i);
	else if ((*token)->token == DOLLARD)
		ft_assemble_dollard(token, cmd, i, lst);
	else
		return (0);
	return (1);
}

void	ft_translate_token(t_list **tmp, t_list *lst)
{
	t_list	*token;
	char	*cmd;
	int		i;
	int		res;

	token = *tmp;
	i = 0;
	ft_fill_size(tmp);
	cmd = (char *)ft_malloc(sizeof(char) * ft_strlen_token(token));
	while (token != NULL)
	{
		res = ft_check_token_associated(&token, &cmd, &i, lst);
		if (res == 2)
			break ;
		else if (res == 0)
		{
			cmd[i] = *(char *)token->content;
			i++;
		}
		token = token->next;
	}
	cmd[i] = '\0';
	ft_fill_translated(tmp, cmd);
}

void	ft_add_token_line(t_list **cmd_token, t_list **tmp, int i, int token)
{
	ft_lstadd_back(cmd_token, ft_lstnew_token
		(ft_substr((*tmp)->cmd_translated, (*tmp)->pos, (*tmp)->j), token));
	(*tmp)->j = 0;
	(*tmp)->pos = i + 1;
}

int	ft_check_assembly(t_list **cmd_token, t_list **tmp, t_list *token, int i)
{
	if (token->cmd_translated[i] == ';' && token->token != QVALUE)
		ft_add_token_line(cmd_token, tmp, i, CMD);
	else if (token->cmd_translated[i] == '>' && token->cmd_translated[i + 1]
		== '>' && token->token != QVALUE)
	{
		i++;
		ft_add_token_line(cmd_token, tmp, i, RD_OA);
	}
	else if (token->cmd_translated[i] == '<' && token->cmd_translated[i + 1]
		== '<' && token->token != QVALUE)
	{
		i++;
		ft_add_token_line(cmd_token, tmp, i, RD_ID);
	}
	else if (token->cmd_translated[i] == '>' && token->token != QVALUE)
		ft_add_token_line(cmd_token, tmp, i, RD_O);
	else if (token->cmd_translated[i] == '<' && token->token != QVALUE)
		ft_add_token_line(cmd_token, tmp, i, RD_I);
	else if (token->cmd_translated[i] == '|' && token->token != QVALUE)
		ft_add_token_line(cmd_token, tmp, i, PIPE);
	else
		return (1);
	return (0);
}

void	ft_assemble_token(t_list **cmd_token, t_list **tmp)
{
	t_list	*token;
	char	**white;
	int		i;

	token = *tmp;
	token->j = 0;
	token->pos = 0;
	while ((*tmp)->cmd_translated[i] || (token != NULL && token->next != NULL))
	{
		if (ft_check_assembly(cmd_token, tmp, token, i))
			(*tmp)->j++;
		if ((*tmp)->cmd_translated[i])
			i++;
		if (token != NULL && token->next != NULL)
			token = token->next;
	}
	if (token != NULL)
		i++;
	white = ft_split(ft_substr((*tmp)->cmd_translated, (*tmp)->pos, i), ' ');
	if (*white == NULL)
		return ;
	else if ((*tmp)->pos != i)
		ft_lstadd_back(cmd_token, ft_lstnew_token
			(ft_substr((*tmp)->cmd_translated, (*tmp)->pos, i), CMD));
}
