/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:08:47 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/16 05:09:17 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing_minishell.h>

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