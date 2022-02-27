/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:31:40 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/27 14:21:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static void	change_env_pwd(t_list *env, char *pathname)
{
	char	*newpwd;
	char	*n;
	int		i;

	newpwd = ft_strjoin(pathname, getcwd(NULL, 0));
	i = 0;
	while (env)
	{
		n = ft_strjoin(ft_before_equal(((t_myenv *)env->content)->env), "=");
		if (ft_strncmp(n, pathname, ft_strlen(pathname)) == 0)
		{
			((t_myenv *)env->content)->env = newpwd;
			((t_myenv *)env->content)->envp[i] = newpwd;
			return ;
		}
		i++;
		env = env->next;
	}
}

void	ft_cd(t_list **cmd)
{
	t_list	*list;
	char	*env;

	list = *cmd;
	change_env_pwd((*cmd)->env, "OLDPWD=");
	if (list->arg[1] == NULL)
	{
		if (getenv("HOME") == NULL)
			write(1, "HOME not set\n", 13);
		else
		{
			env = getenv("HOME");
			chdir(env);
		}
	}
	else if (chdir(list->arg[1]) == -1)
		write(1, "No such file or directory\n", 26);
	change_env_pwd((*cmd)->env, "PWD=");
}
