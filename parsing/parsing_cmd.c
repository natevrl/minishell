/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:10 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 14:24:41y ubuntu           ###   ########.fr       */
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
			if (token->next->next != NULL)
				token->next = token->next->next;
			else
				token->next = NULL;
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
		if (ft_isalnum(*(char *)token->content) || *(char *)token->content == ' ')
			token->token = LITERAL;
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
		else
			token->token = LITERAL;
		token = token->next;
	}
}

void	ft_assemble_token(t_list **cmd_token, t_list **tmp)
{
	t_list	*token;
	char	*cmd;
	char	*env;
	int		i;

	token = *tmp;
	cmd = NULL;
	i = 0;
	cmd = (char *)malloc(sizeof(char) * ft_strlen_token(token));
	while (token != NULL)
	{
		if (token->token == LITERAL)
		{
			cmd[i] = *(char *)token->content;
			i++;
		}
		else if (token->token == EXIT_CODE)
		{
			cmd[i] = '\0';
			i = ft_strlen(cmd) + ft_strlen(ft_itoa(g_err));
			ft_strlcat(cmd, ft_itoa(g_err), i + 1);
		}
		else if (token->token == DOLLARD)
		{
			cmd[i] = *(char *)token->content;
			i++;
			env = ft_get_env((char *)token->content, &token);
			if (getenv(env) != NULL)
			{
				cmd[i - 1] = '\0';
				i = ft_strlen(cmd) + ft_strlen(getenv(env));
				ft_strlcat(cmd, getenv(env), i + 1);
			}
		}
		token = token->next;
	}
	cmd[i] = '\0';
	ft_lstadd_back(cmd_token, ft_lstnew_token(cmd, LITERAL));
}

void	ft_check_execution(t_list **tmp)
{
	t_list	*token;

	token = *tmp;
	while (token != NULL)
	{
		if (token->token == LITERAL)
			exec_cmd(token);
		token = token->next;
	}
}

void	parse_cmd(char *cmd, char **env)
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
	ft_assemble_token(&cmd_token, &token);
	ft_set_option(&cmd_token);
	cmd_token->env = env;
	ft_check_execution(&cmd_token);
}
