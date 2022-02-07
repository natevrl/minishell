/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:10 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/07 14:32:33 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_tokenize_input_condition(t_list **tmp)
{
	t_list	*token;

	token = *tmp;
	while (token != NULL)
	{
		if (token->next != NULL && token->token == PIPE && token->next->token == PIPE)
		{
			token->token = OR;
			token->next->token = OR;
		}
		else if (token->next != NULL && token->token == BG && token->next->token == BG)
		{
			token->token = AND;
			token->next->token = AND;
		}
		else if (token->next != NULL && token->token == RD_I && token->next->token == RD_I)
		{
			token->token = RD_ID;
			token->next->token = RD_ID;
		}
		else if (token->next != NULL && token->token == RD_O && token->next->token == RD_O)
		{
			token->token = RD_OA;
			token->next->token = RD_OA;
		}
		else if (token->next != NULL && token->token == '$' && token->next->token == '?')
		{
			token->token = EXIT_CODE;
			token->next->token = EXIT_CODE;
		}
		token = token->next;
	}
}

void	ft_tokenize_input(t_list **tmp)
{
	t_list	*token;

	token = *tmp;
	while (token != NULL)
	{
		if (ft_isalnum(*(char *)token->content) || *(char *)token->content == ' ' || *(char *)token->content == '-')
			token->token = LITERAL;
		else if (*(char *)token->content == '<')
			token->token = RD_I;
		else if (*(char *)token->content == '>')
			token->token = RD_O;
		else if (*(char *)token->content== '|')
			token->token = PIPE;
		else if (*(char *)token->content == '&')
			token->token = BG;
		else if (*(char *)token->content == '$')
			token->token = DOLLAR;
		else if (*(char *)token->content == ';')
			token->token = EXEC;
		else if (*(char *)token->content == '?')
			token->token = EXIT;
		token = token->next;
	}
}

int	ft_strlen_token(t_list *token)
{
	int	i;

	i = 0;
	while (token->next != NULL && token->token == token->next->token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void	ft_exec_command(t_list **cmd_token, t_list **tmp)
{
	t_list	*token;
	char	*cmd;
	int		i;

	token = *tmp;
	i = 0;
	cmd = (char *)malloc(sizeof(char) * ft_strlen_token(token));
	while (token != NULL)
	{
		if (token->next != NULL && token->token == token->next->token)
		{
			cmd[i] = *(char *)token->content;
			cmd[i + 1] = *(char *)token->next->content;
			i++;
		}
		else
		{
			if (i > 0)
				cmd[i] = '\0';
			ft_lstadd_back(cmd_token, ft_lstnew(cmd));
			i = 0;
			return ;
//			cmd = (char *)malloc(sizeof(char) * ft_strlen_token(token));
		}
		token = token->next;
	}
}

void	parse_cmd(char *cmd)
{
	t_list	*token;
	t_list	*cmd_token;
	int		i;

	i = -1;
	(void)cmd_token;
	token = NULL;
	cmd_token = NULL;
	while (cmd[++i])
		ft_lstadd_back(&token, ft_lstnew(&cmd[i]));
	ft_tokenize_input(&token);
	ft_tokenize_input_condition(&token);
	ft_exec_command(&cmd_token, &token);
	while (cmd_token != NULL)
	{
		printf("%d\n", *(char *)cmd_token->content);
		cmd_token = cmd_token->next;
	}
}
