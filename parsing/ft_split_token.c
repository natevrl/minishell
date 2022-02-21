/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:33:10 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/20 19:35:57by ubuntu           ###   ########.fr       */
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
		while ((token && token->token == QVALUE) || (token && token->token != SP))
			token = token->next;
		cnt++;
		while (token && token->token == SP)
			token = token->next;
	}
	return (cnt);
}

void	ft_check_token(t_list **token, size_t *len, const char **s)
{
	int	count;

	(*len)++;
	count = 0;
	if (*token)
	{
		if ((*token)->token == DOLLARD)
		{
			while (*token && (*token)->next && (*token)->token == DOLLARD && (*token)->next->token == DOLLARD)
			{
				*token = (*token)->next;
				count++;
			}
		}
		else
			*token = (*token)->next;
		if (*token && (*token)->size_env > 0)
		{
			while (*s && (*token)->size_env-- != count)
			{
				++(*s);
				(*len)++;
			}
			*token = (*token)->next;
		}
	}
}

static int	ft_fill(char const *s, char **tab, t_list **tmp)
{
	size_t	i;
	size_t	len;
	t_list	*token;

	i = 0;
	token = *tmp;
	while (*s)
	{
		len = 0;
		while (*s && *s != ' ' && ++s)
			ft_check_token(&token, &len, &s);
		if (token && (token->token == DQUOTE || token->token == QUOTE))
			token = token->next;
		while (token && token->token == QVALUE && *s && ++s)
		{
			len++;
			token = token->next;
		}
		if (token && (token->token == DQUOTE || token->token == DQUOTE))
			token = token->next;
		tab[i] = (char *)ft_malloc(sizeof(char) * len + 1);
		if (!tab[i])
		{
			while (i)
				ft_free(tab[--i]);
			ft_free(tab);
			return (1);
		}
		ft_strlcpy(tab[i++], s - len, len + 1);
		while (token && token->token != QVALUE && token->token != DQUOTE && token->token != QUOTE && *s && *s == ' ')
		{
			token = token->next;
			s++;
		}
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
		s++;
	tab = (char **)ft_malloc(sizeof(char *) * (ft_word(&token) + 1));
	if (!tab)
		return (NULL);
	if (ft_fill(s, tab, &token))
		return (NULL);
	return (tab);
}
