/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:10 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/14 16:36:22buntu           ###   ########.fr       */
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
		else if (token->next != NULL && token->token == DOLLARD && token->next->token == INTERO)
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
		if (ft_isalnum(*(char *)token->content))
			token->token = LITERAL;
		else if (*(char *)token->content == ' ')
			token->token = SP;
		else if (*(char *)token->content == '<')
			token->token = RD_I;
		else if (*(char *)token->content == '>')
			token->token = RD_O;
		else if (*(char *)token->content== '|')
			token->token = PIPE;
		else if (*(char *)token->content == '&')
			token->token = BG;
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
		if (token->token == CMD)
			exec_cmd(token);
		else if (token->token == RD_O)
		{
			if (token->next != NULL)
			{
				while (token->next->token == RD_O)
				{
					token->fd = open(token->next->arg[0], O_CREAT | O_RDWR | O_TRUNC, 0664);
					token = token->next;
				}
				token->fd = open(token->next->arg[0], O_CREAT | O_RDWR | O_TRUNC, 0664);
				redirect_out_cmd((*tmp), token->fd);
				token = token->next;
			}
			else
				ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		}
		else if (token->token == RD_I)
		{
			if (token->next != NULL)
			{
				while (token->next->token == RD_I)
				{
					token->fd = open(token->next->arg[0], O_RDONLY);
					if (token->fd == -1)
					{
						perror(token->next->arg[0]);
						return ;
					}
					redirect_in_cmd((*tmp), token->fd);
					token = token->next;
				}
				token->fd = open(token->next->arg[0], O_RDONLY);
				if (token->fd == -1)
				{
					perror(token->next->arg[0]);
					return ;
				}
				redirect_in_cmd((*tmp), token->fd);
				token = token->next;
			}
			else
				ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		}
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
	ft_set_option(&cmd_token);
	ft_check_execution(&cmd_token, lst);
}
