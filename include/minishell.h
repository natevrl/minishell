/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:13:28 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/17 12:10:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <parsing_minishell.h>
# include <env_minishell.h>
# include <get_next_line.h>
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

int				g_err;

void	exec_cmd(t_list	*cmd);
void	ft_echo(char **argv);
void	ft_pwd(char **argv);
void	ft_cd(t_list **list);
void	ft_export(t_list **list);
void	ft_unset(t_list **list);
void	ft_pipe(t_list **token);
char	*ft_find_path(t_list *lst);
void	sort_and_print_env(char **envp);
void	built_exit(t_list **list);
int		no_equal(char *str);
int		ft_builtin_without_fork(t_list **tmp);
int		launch_bash(t_list	*cmd);
void	prompt(t_list *lst);
void	print_err_code(t_list	*cmd);
void	sig_handler(const int sig);

char	*get_cmd(char **path, char *cmd, char *path_cmd);
void	redirect_out_cmd(t_list	*cmd, int fd);
void	redirect_in_cmd(t_list	*cmd, int fd);
void	here_doc(char *limiter);
char	*ft_get_env_without(char *str);
char	*ft_get_env(char *str, t_list **list);
void	list_push(t_list **lst_addr, void *data);
void	ft_fill_basic_env(char **env, t_list **lst);
void	ft_check_env(char **env, t_list **lst);
size_t	ft_strlen_double(char **str);

int		ft_get_path(t_list *cmd, char **exec_cmd);
void	ft_check_signal(int pid);

void	ft_bultin(t_list **cmd);
void	ft_load_builtin(t_list **list, t_fun *fun, t_ls *ls, char *name);
void	ft_print_env(t_list **lst);
void	ft_update_env(char **env, char *name);

void	ft_exit(int status);
void	exit_failure(const char *msg);
void	*ft_malloc(size_t size);
void	ft_free(void *addr);
void	clear_memory(void);

#endif
