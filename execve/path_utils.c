/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:16:02 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/24 13:22:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_get_path_with_env(t_list *env, t_list *cmd, char **exec_cmd)
{
	char	*path_cmd;
	char	**cmd_path;

	path_cmd = ft_find_env(env->env, "PATH");
	cmd_path = ft_split(path_cmd, ':');
	if (cmd->arg[0] == NULL)
		return (1);
	*exec_cmd = get_cmd(cmd_path, cmd->arg[0], path_cmd);
	return (0);
}

int	ft_get_path_with_env_arg(t_list *env, t_list *cmd, char **exec_cmd)
{
	char	*path_cmd;
	char	**cmd_path;
	int		i;

	path_cmd = ft_find_env(env->env, "PATH");
	cmd_path = ft_split(path_cmd, ':');
	if (!cmd->arg || cmd->arg[0] == NULL)
		return (1);
	i = 0;
	while (cmd->arg[i + 1])
	{
		cmd->arg[i] = cmd->arg[i + 1];
		i++;
	}
	cmd->arg[i] = NULL;
	*exec_cmd = get_cmd(cmd_path, cmd->arg[0], path_cmd);
	return (0);
}
