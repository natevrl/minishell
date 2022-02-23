/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:27:35 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/23 17:29:14 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_check_env_count(t_list **token)
{
	if ((*token)->token == DOLLARD)
	{
		while (*token && (*token)->next && (*token)->token
			== DOLLARD && (*token)->next->token == DOLLARD)
		{
			*token = (*token)->next;
		}
	}
	else
		*token = (*token)->next;
}

void	ft_check_token(t_list **token, size_t *len, const char **s)
{
	if (*token)
	{
		ft_check_env_count(token);
		if (*token && (*token)->size_env > 0)
		{
			while (*s && (*token)->size_env-- > 2)
			{
				++(*s);
				(*len)++;
			}
			*token = (*token)->next;
		}
	}
	++(*s);
	(*len)++;
}
