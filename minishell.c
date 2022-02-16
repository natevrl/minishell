/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:54:36 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/16 05:23:01 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	prompt(t_list *lst)
{
	char	*cmd;

	cmd = readline("$> ");
	if (!cmd)
	{
		write(1, "exit\n", 5);
		ft_exit(g_err);
	}
	add_history(cmd);
	if (*cmd == '\0')
		return ;
	parse_cmd(cmd, lst);
}

int	main(int ac, char **av, char **env)
{
	t_list	*lst;

	(void)ac;
	(void)av;
	g_err = 0;
	lst = NULL;
	ft_check_env(env, &lst);
	return (launch_bash(lst));
}
