/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:31:40 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 22:36:42 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * CAS a gerer pour CD :
 * a chaque cd, le OLDPWD et PWD path changent, mettre a jour l'env
 * ~/ pour le HOME
 * cd -- pour le HOME
 * cd - = OLDPWD du l'env
 */

char *own_getenv(char *pathname, t_list *begin)
{
	t_list *tmp;
	char *lst_name;

	tmp = begin;
	while (tmp)
	{
		lst_name = before_equal((char *)tmp->content);
		if (ft_strncmp(lst_name, pathname, 100) == 0)
		{
			free(lst_name);
			return (tmp->content);
		}
		tmp = tmp->next;
		free(lst_name);

	}
	return (NULL);
}


void	change_env_pwd(t_list *envlist, char *pathname)
{
	char	*newpwd;
	char *lst_name;

	newpwd = getcwd(NULL, 0);
	newpwd = ft_strjoin(pathname, newpwd);
	printf("====================  %s\n", newpwd);

	while (envlist)
	{
		lst_name = before_equal((char *)envlist->content);
		if (ft_strncmp(lst_name, pathname, 100) == 0)
		{
			envlist->content = newpwd;
			free(lst_name);
			return ;
		}
		envlist = envlist->next;
	}
	free(lst_name);
	free(newpwd);
}

void ft_cd(t_list *list)
{
    ft_pwd();
	change_env_pwd(list->env, "OLDPWD=");
    if (chdir(list->env[1]) != 0)
        perror("change directory failed");
	change_env_pwd(list->env, "PWD=");
    ft_pwd();
}
