/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:07:46 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/16 11:39:54 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	no_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (0);
	return (1);
}

char	*before_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
	return (NULL);
}

char	*after_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (str + i + 1);
	return (NULL);
}


// check si la variable est deja dans l'env
// return 1 si la variable + sa valeur sont dans l'env
// return 1 + change la valeur, si elle est differente
int	already_in_env(t_list **cmd, char *arg)
{
	// char	*cmp1;
	char	*cmp2;
	t_list *envlist;

	envlist = *cmd;
	while (envlist->env)
	{
		// printf("%s\n", ((t_myenv *)envlist->env->content)->name);
		// // cmp1 = before_equal(envlist->content);
		cmp2 = before_equal(arg);
		if (ft_strncmp(((t_myenv *)envlist->env->content)->name, cmp2, 100) == 0)
		{
			if (ft_strncmp(((t_myenv *)envlist->env->content)->value, after_equal(arg), 100) != 0)
				((t_myenv *)envlist->env->content)->env = arg;
			return (1);
		}
		envlist->env = envlist->env->next;
	}
	return (0);
}


// static void	print_export(t_list *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("%s %s\n", "declare -x", (char *)cmd->content);
// 		cmd = cmd->next;
// 	}
// }

// static void	str_swap(void **s1, void **s2)
// {
// 	char	*tampon;

// 	tampon = *s1;
// 	*s1 = *s2;
// 	*s2 = tampon;
// }

// ne va pas fonctionner si on ajoute puis export sans arg, a tester
// utiliser plutot un tmp de cmd
// static void	sort_and_print_env(char **env)
// {
// 	t_list	*begin;
// 	t_list	*i;
// 	t_list	*y;

// 	i = ft_init_env(env);
// 	begin = i;
// 	while (i->next)
// 	{
// 		y = i->next;
// 		while (y->next)
// 		{
// 			if (ft_strncmp(i->content, y->content, 100) > 0)
// 				str_swap(&i->content, &y->content);
// 			y = y->next;
// 		}
// 		i = i->next;
// 	}
// 	print_export(begin);
// }


void	add_new_envlist(t_list **list, char *arg)
{
	t_myenv *t;

	t = (t_myenv *)ft_malloc(sizeof(t_myenv));
	t->name = before_equal(arg);
	t->value = ft_strdup(after_equal(arg));
	t->env = ft_strdup(arg);
	t->envp = NULL;
	list_push(&(*list)->env, t);
}

void	ft_export(t_list **list)
{
	t_list	*envlist;
//	int		i;

	envlist = *list;
	if (envlist->arg[1] == NULL)
		sort_and_print_env(((t_myenv *)(*list)->env->content)->envp);
//	i = 0;
// 	sort_and_print_env(((t_myenv *)(*list)->env->content)->envp);
//	i = -1;
/*	while (envlist->arg[++i])
	{
//		if (no_equal(envlist->arg[i]))
//			continue ;
//		if (already_in_env(list, envlist->arg[i]))
//			continue ;
		add_new_envlist(list, envlist->arg[i]);
		printf("OK\n");
	}*/
}
