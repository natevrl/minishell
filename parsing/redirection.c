/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 06:04:18 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/26 01:25:19 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_loop_redir(t_list **token)
{
	while ((*token)->next->token == RD_O)
	{
		(*token)->fd = open((*token)->next->arg[0],
				O_CREAT | O_RDWR | O_TRUNC, 0664);
		close((*token)->fd);
		*token = (*token)->next;
	}
}

void	ft_loop_redira(t_list **token)
{
	while ((*token)->next->token == RD_OA)
	{
		(*token)->fd = open((*token)->next->arg[0],
				O_CREAT | O_RDWR | O_CREAT | O_APPEND, 0664);
		close((*token)->fd);
		*token = (*token)->next;
	}
}

void	ft_redirect_to_output(t_list **token, t_list **tmp)
{
	if ((*token)->next != NULL)
	{
		while ((*token)->next->token == RD_OA || (*token)->next->token == RD_O)
		{
			if ((*token)->next->token == RD_OA)
				ft_loop_redira(token);
			else
				ft_loop_redir(token);
		}
		if ((*token)->token == RD_O || (*token)->token == RD_OA)
		{
			if ((*token)->token == RD_O)
				(*token)->fd = open((*token)->next->arg[0],
						O_CREAT | O_RDWR | O_TRUNC, 0664);
			else
				(*token)->fd = open((*token)->next->arg[0],
					O_CREAT | O_RDWR | O_APPEND, 0664);
			redirect_out_cmd((*tmp), (*token)->fd);
			close((*token)->fd);
			*token = (*token)->next->next;
		}
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		*token = (*token)->next;
	}
}

void	ft_input_to_heredoc(t_list **token)
{
	if ((*token)->next != NULL)
	{
		while ((*token)->next->token == RD_ID)
		{
			here_doc((*token)->next->arg[0]);
			*token = (*token)->next;
		}
		here_doc((*token)->next->arg[0]);
		*token = (*token)->next;
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		*token = (*token)->next;
	}
}

int	ft_redirect_input_loop(t_list **token)
{
	while ((*token)->next->token == RD_I)
	{
		(*token)->fd = open((*token)->next->arg[0], O_RDONLY);
		if ((*token)->fd == -1)
		{
			err_found_msg((*token)->next->arg[0], 0);
			while ((*token) && (*token)->token != PIPE)
				*token = (*token)->next;
			return (1);
		}
		close((*token)->fd);
		*token = (*token)->next;
	}
	return (0);
}

void	ft_redirect_input(t_list **token, t_list **tmp)
{
	if ((*token)->next != NULL)
	{
		if (ft_redirect_input_loop(token))
			return ;
		if ((*token)->token == RD_I)
		{
			(*token)->fd = open((*token)->next->arg[0], O_RDONLY);
			if ((*token)->fd == -1)
			{
				err_found_msg((*token)->next->arg[0], 0);
				while (*token && (*token)->token != PIPE)
					*token = (*token)->next;
				return ;
			}
			if (*(*token)->arg)
				redirect_in_cmd((*tmp), (*token)->fd);
			else if ((*tmp)->next->arg[1])
				redirect_in_cmd2((*tmp), (*tmp)->next, (*token)->fd);
			close((*token)->fd);
			*token = (*token)->next->next;
		}
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		*token = (*token)->next;
	}
}
