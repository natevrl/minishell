/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:08:47 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/21 18:19:07 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing_minishell.h>

int	ft_assemble_quote(t_list **token, char **cmd, int *i)
{
	*token = (*token)->next;
	while (*token != NULL && (*token)->token != QUOTE)
	{
		(*token)->token = QVALUE;
		(*cmd)[*i] = *(char *)(*token)->content;
		(*i)++;
		*token = (*token)->next;
	}
	if ((*token) == NULL)
	{
		printf("Not closed quote\n");
		return (1);
	}
	return (0);
}

void	ft_assemble_dollard(t_list **token, char **cmd, int *i, t_list *lst)
{
	char	*env;

	(void)lst;
	env = ft_get_env((char *)(*token)->content, token);
	if (ft_strlen(env) == 0)
	{
		(*cmd)[*i] = *(char *)(*token)->content;
		(*i)++;
	}
	if (ft_find_env(lst, env) != NULL)
	{
		(*token)->token = DOLLARD;
		(*token)->size_env = ft_strlen(ft_find_env(lst, env));
		(*cmd)[*i] = '\0';
		*i = ft_strlen(*cmd) + ft_strlen(ft_find_env(lst, env));
		ft_strlcat(*cmd, ft_find_env(lst, env), (*i) + 1);
	}
}

void	ft_assemble_exit(t_list **token, char **cmd, int *i)
{
	(*cmd)[*i] = '\0';
	*i = ft_strlen(*cmd) + ft_strlen(ft_itoa(g_err));
	ft_strlcat(*cmd, ft_itoa(g_err), *i + 1);
	*token = (*token)->next;
}

int	ft_assemble_dquote(t_list **token, char **cmd, int *i, t_list *lst)
{
	(*token) = (*token)->next;
	while (*token != NULL && (*token)->token != DQUOTE)
	{
		if ((*token)->token == EXIT_CODE)
			ft_assemble_exit(token, cmd, i);
		else if ((*token)->token == DOLLARD)
			ft_assemble_dollard(token, cmd, i, lst);
		else
		{
			(*token)->token = QVALUE;
			(*cmd)[*i] = *(char *)(*token)->content;
			(*i)++;
		}
		(*token) = (*token)->next;
	}
	if (*token == NULL)
	{
		printf("Not closed quote\n");
		return (1);
	}
	return (0);
}
