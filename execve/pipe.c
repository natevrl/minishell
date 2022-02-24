/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:18:35 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/24 13:23:54 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipe_exec(t_list **token, t_list **cmp, char *exec_tube1)
{
	ft_bultin(token);
	if (ft_builtin_without_fork(token))
		ft_exit(g_err);
	g_err = execve(exec_tube1, (*token)->arg,
			((t_myenv *)(*cmp)->env->content)->envp);
	if (g_err == -1)
		exit_failure((*token)->arg[0]);
	ft_exit(g_err);
}

void	dup_read(int i, int fdr)
{
	if (i > 0)
		dup2(fdr, 0);
	else
		signal(SIGQUIT, sig_handler);
}

void	pipe_loop(t_list **token, t_list **cmp, int fdr, int i)
{
	int		fd[2];
	int		pid;
	char	*exec_tube1;

	while ((*token) != NULL)
	{
		if (ft_get_path_with_env(*cmp, *token, &exec_tube1))
			exit_failure("invalid cmd");
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup_read(i, fdr);
			if ((*token)->next != NULL)
				dup2(fd[1], 1);
			ft_close(fd);
			close(fdr);
			pipe_exec(token, cmp, exec_tube1);
		}
		dup2(fd[0], fdr);
		ft_close(fd);
		*token = (*token)->next;
		i++;
	}
}

int	ft_parse_pipe(t_list **token, t_list **cmp)
{
	t_list	*parse;

	parse = *token;
	while (parse)
	{
		if (!parse->arg[0])
		{
			if (number_of_pipe(cmp) == 1)
				printf("minishell: syntax error near unexpected token `|'\n");
			else
				printf("minishell: syntax error near unexpected token `||'\n");
			while (*token)
				*token = (*token)->next;
			return (1);
		}
		else if (finished_with_pipe(cmp))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			while (*token)
				*token = (*token)->next;
			return (1);
		}
		parse = parse->next;
	}
	return (0);
}

void	ft_pipe(t_list **token, t_list **cmp)
{
	int	fdr;
	int	i;

	if (ft_parse_pipe(token, cmp))
		return ;
	pipe_loop(token, cmp, fdr = dup(0), i = 0);
	close(fdr);
	i = -1;
	while (++i <= number_of_pipe(cmp))
		ft_check_signal(0);
}
