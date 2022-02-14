/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:53:49 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/14 12:02:06 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_get_env_without(char *str)
{
	char	*env;
	int		i;

	i = 0;
	env = NULL;
	if (str[i] == '$')
	{
		i++;
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
			i++;
		env = ft_substr(str, 1, i - 1);
		return (env);
	}
	return (NULL);
}

char	*ft_get_env(char *str, t_list **list)
{
	char	*env;
	int		i;

	i = 0;
	env = NULL;
	if (str[i] == '$')
	{
		i++;
		while (str[i] != '\0' && str[i] != ' '  && str[i] != '$' &&
			str[i] != '\"' && str[i] != '=' && str[i] != '+')
		{
			i++;
			*list = (*list)->next;
		}
		env = ft_substr(str, 1, i - 1);
		return (env);
	}
	return (NULL);
}

size_t	ft_strlen_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_load_env(t_list **list, char *env, char **envp)
{
	t_myenv *t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_before_equal(env);
	t->value = ft_after_equal(env);
	t->env = ft_strdup(env);
	t->envp = envp;
	list_push(list, t);
}

void	ft_fill_basic_env(char **env, t_list **lst)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_load_env(lst, env[i], env);
		i++;
	}
}

void	ft_add_under(char **envp, t_list **list)
{
	t_myenv *t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_strdup("_");
	t->value = ft_strdup("/usr/bin/env");
	t->env = ft_strdup("_=/usr/bin/env");
	t->envp = envp;
	list_push(list, t);
}

void	ft_add_pwd(char **envp, t_list **list)
{
	t_myenv *t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_strdup("PWD");
	t->value = ft_strdup("/");
	t->env = ft_strdup("PWD=/");
	t->envp = envp;
	list_push(list, t);
}

void	ft_add_shlvl(char **envp, t_list **list)
{
	t_myenv *t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = ft_strdup("SHLVL");
	t->value = ft_strdup("1");
	t->env = ft_strdup("SHLVL=1");
	t->envp = envp;
	list_push(list, t);
}

void	ft_find_add_env(char **envp, t_list **lst_env, char *name)
{
	t_list	*list;

	list = *lst_env;
	while (list && ft_strncmp(((t_myenv *)list->content)->name, name, ft_strlen(name)) != 0)
		list = list->next;
	if (((t_myenv *)list->content) == NULL)
	{
		if (ft_strncmp(name, "_", 4) == 0)
			ft_add_under(envp, lst_env);
		else if (ft_strncmp(name, "SHLVL", 5) == 0)
			ft_add_shlvl(envp, lst_env);
		else if (ft_strncmp(name, "PWD", 3) == 0)
			ft_add_pwd(envp, lst_env);
	}
	else
		return ;
}

void	ft_check_required(char **envp, t_list **lst)
{
	if (*lst)
	{
		if (ft_strncmp("_", ((t_myenv *)(*lst)->content)->name, 1) != 0)
			ft_find_add_env(envp, lst, "_");
		if (ft_strncmp("SHLVL", ((t_myenv *)(*lst)->content)->name, 5) != 0)
			ft_find_add_env(envp, lst, "SHLVL");
		if (ft_strncmp("PWD", ((t_myenv *)(*lst)->content)->name, 3) != 0)
			ft_find_add_env(envp, lst, "PWD");
	}
	else
	{
		ft_add_pwd(envp, lst);
		ft_add_shlvl(envp, lst);
		ft_add_under(envp, lst);
	}
}

void	ft_check_env(char **env, t_list **lst)
{
	ft_fill_basic_env(env, lst);
	ft_check_required(env, lst);
}
