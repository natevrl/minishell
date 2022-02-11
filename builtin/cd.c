/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:31:40 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 22:45:55 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int no_equal(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (0);
	return (1);
}

char *before_equal(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
	return (NULL);
}

char *after_equal(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (str + i + 1);
	return (NULL);
}

int already_in_env(t_list *envlist, char *arg)
{
	char *cmp1;
	char *cmp2;

	while (envlist)
	{
		cmp1 = before_equal(envlist->content);
		cmp2 = before_equal(arg);
		if (ft_strncmp(cmp1, cmp2, 100) == 0)
		{
			if (ft_strncmp(after_equal(envlist->content), after_equal(arg), 100) != 0)
				envlist->content = arg;
			free(cmp1);
			free(cmp2);
			return (1);
		}
		free(cmp1);
		free(cmp2);
		envlist = envlist->next;
	}
	return (0);
}

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


void	change_env_pwd(char **list, char *pathname)
{
	char	*newpwd;
	int		i;
	char *lst_name;

	i = 0;
	newpwd = getcwd(NULL, 0);
	newpwd = ft_strjoin(pathname, newpwd);
	printf("====================  %s\n", newpwd);
	while (list[i])
	{
		lst_name = before_equal(list[i]);
		if (ft_strncmp(lst_name, pathname, 100) == 0)
		{
			list[i] = newpwd;
			free(lst_name);
			return ;
		}
		i++;
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
