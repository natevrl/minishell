/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 06:04:18 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/16 13:24:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_redirect_to_output(t_list **token, t_list **tmp)
{
	if ((*token)->next != NULL)
	{
		while ((*token)->next->token == RD_O)
		{
			(*token)->fd = open((*token)->next->arg[0],
					O_CREAT | O_RDWR | O_TRUNC, 0664);
			*token = (*token)->next;
		}
		(*token)->fd = open((*token)->next->arg[0],
				O_CREAT | O_RDWR | O_TRUNC, 0664);
		redirect_out_cmd((*tmp), (*token)->fd);
		*token = (*token)->next;
	}
	else
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
}

void	ft_input_to_heredoc(t_list **token)
{
	if ((*token)->next != NULL)
	{
		while ((*token)->next->token == RD_OA)
		{
			here_doc((*token)->next->arg[0]);
			*token = (*token)->next;
		}
		here_doc((*token)->next->arg[0]);
		*token = (*token)->next;
	}
	else
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
}

void	ft_redirect_to_outputa(t_list **token, t_list **tmp)
{
	if ((*token)->next != NULL)
	{
		while ((*token)->next->token == RD_OA)
		{
			(*token)->fd = open((*token)->next->arg[0],
					O_CREAT | O_RDWR | O_CREAT | O_APPEND, 0664);
			*token = (*token)->next;
		}
		(*token)->fd = open((*token)->next->arg[0],
				O_CREAT | O_RDWR | O_APPEND, 0664);
		redirect_out_cmd((*tmp), (*token)->fd);
		*token = (*token)->next;
	}
	else
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
}

void	ft_redirect_input(t_list **token, t_list **tmp)
{
	if ((*token)->next != NULL)
	{
		while ((*token)->next->token == RD_I)
		{
			(*token)->fd = open((*token)->next->arg[0], O_RDONLY);
			if ((*token)->fd == -1)
			{
				perror((*token)->next->arg[0]);
				return ;
			}
			redirect_in_cmd((*tmp), (*token)->fd);
			*token = (*token)->next;
		}
		(*token)->fd = open((*token)->next->arg[0], O_RDONLY);
		if ((*token)->fd == -1)
		{
			perror((*token)->next->arg[0]);
			return ;
		}
		redirect_in_cmd((*tmp), (*token)->fd);
		*token = (*token)->next;
	}
	else
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
}
