/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 06:04:18 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/17 16:57:49 by ubuntu           ###   ########.fr       */
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
			close((*token)->fd);
			*token = (*token)->next;
		}
		(*token)->fd = open((*token)->next->arg[0],
				O_CREAT | O_RDWR | O_TRUNC, 0664);
		redirect_out_cmd((*tmp), (*token)->fd);
		close((*token)->fd);
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
			close((*token)->fd);
			*token = (*token)->next;
		}
		(*token)->fd = open((*token)->next->arg[0],
				O_CREAT | O_RDWR | O_APPEND, 0664);
		redirect_out_cmd((*tmp), (*token)->fd);
		close((*token)->fd);
		*token = (*token)->next;
	}
	else
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
}

void	redirect_in_cmd2(t_list	*cmd, t_list *arg, int fd)
{
	pid_t	pid;
	char	*exec_cmd;

	if (ft_get_path_with_env_arg(cmd, arg, &exec_cmd) || ft_builtin_without_fork(&arg))
		return ;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
		ft_check_signal(pid);
	else
	{
		signal(SIGQUIT, sig_handler);
		dup2(fd, STDIN_FILENO);
		close(fd);
		ft_bultin(&arg);
		g_err = execve(exec_cmd, arg->arg,
				((t_myenv *)cmd->env->content)->envp);
		if (g_err == -1)
			exit_failure("command not found");
		ft_exit(g_err);
	}
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
				while ((*token)->token == RD_I)
					*token = (*token)->next;
				return ;
			}
			close((*token)->fd);
			*token = (*token)->next;
		}
		(*token)->fd = open((*token)->next->arg[0], O_RDONLY);
		if ((*token)->fd == -1)
		{
			perror((*token)->next->arg[0]);
			return ;
		}
		if (*(*token)->arg)
			redirect_in_cmd((*tmp), (*token)->fd);
		else
			redirect_in_cmd2((*tmp), (*tmp)->next, (*token)->fd);
		close((*token)->fd);
		*token = (*token)->next;
	}
	else
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
}
