/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:10 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/20 18:36:10 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_token(t_list **token, int t)
{
	(*token)->token = t;
	(*token)->next->token = t;
}

void	ft_tokenize_input_condition(t_list **tmp)
{
	t_list	*token;

	token = *tmp;
	while (token != NULL)
	{
		if (token->next != NULL && token->token == PIPE
			&& token->next->token == PIPE)
			set_token(&token, OR);
		else if (token->next != NULL && token->token == RD_I
			&& token->next->token == RD_I)
			set_token(&token, RD_ID);
		else if (token->next != NULL && token->token == RD_O
			&& token->next->token == RD_O)
			set_token(&token, RD_OA);
		else if (token->next != NULL && token->token == DOLLARD
			&& token->next->token == INTERO)
			set_token(&token, EXIT_CODE);
		token = token->next;
	}
}

void	ft_tokenize_input(t_list **tmp)
{
	t_list	*token;

	token = *tmp;
	while (token != NULL)
	{
		if (ft_isalnum(*(char *)token->content))
			token->token = LITERAL;
		else if (*(char *)token->content == ' ')
			token->token = SP;
		else if (*(char *)token->content == '<')
			token->token = RD_I;
		else if (*(char *)token->content == '>')
			token->token = RD_O;
		else if (*(char *)token->content == '|')
			token->token = PIPE;
		else if (*(char *)token->content == ';')
			token->token = EXEC;
		else if (*(char *)token->content == '$')
			token->token = DOLLARD;
		else if (*(char *)token->content == '?')
			token->token = INTERO;
		else if (*(char *)token->content == '\'')
			token->token = QUOTE;
		else if (*(char *)token->content == '\"')
			token->token = DQUOTE;
		else
			token->token = LITERAL;
		token = token->next;
	}
}

void	ft_check_execution(t_list **tmp, t_list *lst)
{
	t_list	*token;

	token = *tmp;
	while (token != NULL)
	{
		token->env = lst;
		if (token->token == CMD || QVALUE)
			exec_cmd(token);
		else if (token->token == RD_O)
			ft_redirect_to_output(&token, tmp);
		else if (token->token == RD_ID)
			ft_input_to_heredoc(&token);
		else if (token->token == RD_OA)
			ft_redirect_to_outputa(&token, tmp);
		if (token->token == RD_I)
			ft_redirect_input(&token, tmp);
		if (token->token == PIPE)
			ft_pipe(&token, tmp);
		else
			token = token->next;
	}
}

void	parse_cmd(char *cmd, t_list *lst)
{
	t_list	*token;
	t_list	*cmd_token;
	int		i;

	i = -1;
	token = NULL;
	cmd_token = NULL;
	while (cmd[++i])
		ft_lstadd_back(&token, ft_lstnew(&cmd[i]));
	ft_tokenize_input(&token);
	ft_tokenize_input_condition(&token);
	ft_translate_token(&token);
	ft_assemble_token(&cmd_token, &token);
	ft_set_option(&cmd_token, &token);
	ft_check_execution(&cmd_token, lst);
}
