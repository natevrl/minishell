/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:19:22 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/25 23:40:22 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_word(t_list **tmp)
{
	size_t	cnt;
	t_list	*token;

	cnt = 0;
	token = *tmp;
	while (token)
	{
		while ((token && token->token == QVALUE)
			|| (token && token->token != SP))
		{
			if (token && token->next && ((token->token == DQUOTE
						&& token->next->token == DQUOTE) || (token->token
						== QUOTE && token->next->token == QUOTE)))
			{
				token = token->next;
				break ;
			}
			token = token->next;
		}
		cnt++;
		while (token && token->token == SP)
			token = token->next;
	}
	return (cnt);
}

static void	ft_check_token_split(t_list **token, size_t *len, const char **s)
{
	if (*token && ((*token)->token == DQUOTE || (*token)->token == QUOTE))
		*token = (*token)->next;
	while (*token && ((*token)->token == QVALUE
			|| (*token)->token == DOLLARD) && *(*s))
	{
		if ((*token) && ((*token)->token == DOLLARD))
			ft_check_token(token, len, s);
		else
			*token = (*token)->next;
		(*len)++;
		++(*s);
	}
	if ((*token) && ((*token)->token == DQUOTE || (*token)->token == QUOTE))
		*token = (*token)->next;
}

static int	ft_fill(char const *s, char **tab, t_list **token)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		ft_check_token_split(token, &len, &s);
		while (*s && *s != ' ')
			ft_check_token(token, &len, &s);
		tab[i] = (char *)ft_malloc(sizeof(char) * len + 1);
		if (!tab[i])
		{
			while (i)
				ft_free(tab[--i]);
			ft_free(tab);
			return (1);
		}
		ft_strlcpy(tab[i++], s - len, len + 1);
		while (*token && (*token)->token != QVALUE && *s && *s == ' ' && *s++)
			*token = (*token)->next;
	}
	tab[i] = 0;
	return (0);
}

char	**ft_split_token(const char *s, t_list *token)
{
	char	**tab;

	if (!s)
		return (NULL);
	while (*s == ' ' && *s)
	{
		token = token->next;
		s++;
	}
	tab = (char **)ft_malloc(sizeof(char *) * (ft_word(&token) + 1));
	if (!tab)
		return (NULL);
	if (ft_fill(s, tab, &token))
		return (NULL);
	return (tab);
}
