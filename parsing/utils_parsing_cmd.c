/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:54 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/06 14:05:04 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing_minishell.h>

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_token(t_token **alst, t_token *new)
{
	t_token	*tmp;

	if (alst)
	{
		if (*alst)
		{
			tmp = ft_lstlast_token(*alst);
			tmp->next = new;
		}
		else
			*alst = new;
	}
}

t_token	*ft_lstnew_token(char c)
{
	t_token	*list;

	list = (t_token *)malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->c = c;
	list->next = NULL;
	return (list);
}
