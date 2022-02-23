/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:07:59 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/21 20:08:47by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	number_of_pipe(t_list **token)
{
	t_list	*tmp;
	int		i;

	tmp = *token;
	i = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	pipe_exec(t_list **token, t_list **cmp, char *exec_tube1)
{
	ft_builtin_without_fork(token);
	g_err = execve(exec_tube1, (*token)->arg,
			((t_myenv *)(*cmp)->env->content)->envp);
	if (g_err == -1)
		exit_failure((*token)->arg[0]);
	ft_exit(g_err);
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
			if (i > 0)
				dup2(fdr, 0);
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

// gerer les builtins = export | grep USER
// quand plein de ||||| = pleins de messages d'erreur
void	ft_pipe(t_list **token, t_list **cmp)
{
	int	fdr;
	int	i;

	if (!(*token)->arg[0])
	{
		if (number_of_pipe(cmp) == 1)
			printf("minishell: syntax error near unexpected token `|'\n");
		else
			printf("minishell: syntax error near unexpected token `||'\n");
		(*token) = (*token)->next;
		return ;
	}
	pipe_loop(token, cmp, fdr = dup(0), i = 0);
	close(fdr);
	i = -1;
	while (++i <= number_of_pipe(cmp))
		wait(NULL);
}

