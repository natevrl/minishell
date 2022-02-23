/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:12:10 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/23 14:34:46 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <minishell.h>
# include <redirection.h>
# include <libft.h>

typedef void	t_fun(char **arg);
typedef void	t_ls(t_list **arg);

typedef struct s_myenv {
	char			*name;
	char			*value;
	char			*env;
	char			**envp;
	struct s_myenv	*next;
}				t_myenv;

typedef struct s_builtin {
	char	*name;
	t_fun	*built;
	t_ls	*built_l;
	t_ls	*built_lm;
}				t_builtin;

void	ft_echo(char **argv);
void	ft_pwd(char **argv);
void	ft_cd(t_list **list);
void	ft_export(t_list **list);
void	ft_fill_env(char *arg, t_list *cmd, char **env);
void	ft_unset(t_list **list);

void	ft_bultin(t_list **cmd);
void	ft_load_builtin(t_list **list, t_fun *fun, t_ls *ls, char *name);
int		ft_builtin_without_fork(t_list **tmp);
void	built_exit(t_list **list);

#endif
