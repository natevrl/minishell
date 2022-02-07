/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:03:10 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/07 12:11:21 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	ft_tokenize_input_condition(t_token **token)
{
	printf("%d\n", (*token)->token);

}*/

void	ft_tokenize_input(t_list **token)
{
	while (*token != NULL)
	{
		if (ft_isalnum(*(char *)(*token)->content) || *(char *)(*token)->content == ' ')
			(*token)->token = LITERAL;
		if (*(char *)(*token)->content == '<')
			(*token)->token = RD_I;
		else if (*(char *)(*token)->content == '>')
			(*token)->token = RD_O;
		else if (*(char *)(*token)->content== '|')
			(*token)->token = PIPE;
		else if (*(char *)(*token)->content == '&')
			(*token)->token = BG;
		printf("%d\n", (*token)->token);
		*token = (*token)->next;
	}
}

void	parse_cmd(char *cmd)
{
	t_list	*token;
	int		i;

	i = -1;
	token = NULL;
	while (cmd[++i])
		ft_lstadd_back(&token, ft_lstnew(&cmd[i]));
	ft_tokenize_input(&token);
//	ft_tokenize_input_condition(&token);
}
