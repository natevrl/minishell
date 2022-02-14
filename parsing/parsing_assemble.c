/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assemble.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:15:33 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/14 17:32:40 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_assemble_quote(t_list **token, char **cmd, int *i)
{
	*token = (*token)->next;
	while (*token != NULL && (*token)->token != QUOTE)
	{
		(*cmd)[*i] = *(char *)(*token)->content;
		(*i)++;
		*token = (*token)->next;
	}
	if ((*token) == NULL)
	{
		printf("Not closed quote\n");
		exit(1);
	}
}

void	ft_assemble_dollard(t_list **token, char **cmd, int *i)
{
	char	*env;

	env = ft_get_env((char *)(*token)->content, token);
	if (ft_strlen(env) == 0)
	{
		(*cmd)[*i] = *(char *)(*token)->content;
		(*i)++;
	}
	if (getenv(env) != NULL)
	{
		(*cmd)[*i] = '\0';
		*i = ft_strlen(*cmd) + ft_strlen(getenv(env));
		ft_strlcat(*cmd, getenv(env), (*i) + 1);
	}
}

void	ft_assemble_exit(t_list **token, char **cmd, int *i)
{
	(*cmd)[*i] = '\0';
	*i = ft_strlen(*cmd) + ft_strlen(ft_itoa(g_err));
	ft_strlcat(*cmd, ft_itoa(g_err), *i + 1);
	*token = (*token)->next;
}

void	ft_assemble_dquote(t_list **token, char **cmd, int *i)
{
	*token = (*token)->next;
	while (*token != NULL && (*token)->token != DQUOTE)
	{
		if ((*token)->token == EXIT_CODE)
			ft_assemble_exit(token, cmd, i);
		else if ((*token)->token == DOLLARD)
			ft_assemble_dollard(token, cmd, i);
		else
		{
			(*cmd)[*i] = *(char *)(*token)->content;
			(*i)++;
		}
		*token = (*token)->next;
	}
	if (*token == NULL)
	{
		printf("Not closed quote\n");
		exit(1);
	}
}

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
	cmd = (char *)malloc(sizeof(char) * ft_strlen_token(token));
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
		{
			ft_lstadd_back(cmd_token, ft_lstnew_token(ft_substr((*tmp)->cmd_translated, pos, j), CMD));
			j = 0;
			pos = i + 1;
		}
		else if (token->cmd_translated[i] == '<')
		{
			ft_lstadd_back(cmd_token, ft_lstnew_token(ft_substr((*tmp)->cmd_translated, pos, j), RD_I));
			j = 0;
			pos = i + 1;
		}
		else if (token->cmd_translated[i] == '>')
		{
			ft_lstadd_back(cmd_token, ft_lstnew_token(ft_substr((*tmp)->cmd_translated, pos, j), RD_O));
			j = 0;
			pos = i + 1;
		}
		else if (token->cmd_translated[i] == '<')
		{
			ft_lstadd_back(cmd_token, ft_lstnew_token(ft_substr((*tmp)->cmd_translated, pos, j), RD_I));
			j = 0;
			pos = i + 1;
		}
		else
			j++;
		i++;
	}
	ft_lstadd_back(cmd_token, ft_lstnew_token(ft_substr((*tmp)->cmd_translated, pos, i), CMD));
}
