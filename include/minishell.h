/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:13:28 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/11 22:27:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <parsing_minishell.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <err.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

//ajout
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef void	t_fun(char **arg);
typedef void	t_ls(t_list *arg);

typedef struct s_builtin {
	char	*name;
	t_fun	*built;
}				t_builtin;

typedef struct s_builtin_list {
	char	*name;
	t_ls	*built;
}				t_builtin_ls;

int		g_err;

void	exec_cmd(t_list	*cmd);
void	ft_echo(char **argv);
void	ft_pwd(char **arg);
int		launch_bash(char **env);
void	prompt(char **env);
void	print_err_code(t_list	*cmd);
void	intHandler(int sig);

char	*ft_get_env_without(char *str);
char	*ft_get_env(char *str, t_list **list);

void	ft_bultin(t_list **cmd);
void	ft_load_builtin(t_list **list, t_fun *fun, char *name);
void	ft_print_env(t_list *lst);

void	ft_exit(int status);
void	exit_failure(const char *msg);
void	*ft_malloc(size_t size);
void	ft_free(void *addr);
void	clear_memory(void);

#endif
