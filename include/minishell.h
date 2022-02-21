/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:13:28 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/21 14:32:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <parsing_minishell.h>
# include <env_minishell.h>
# include <builtin.h>
# include <get_next_line.h>
# include <redirection.h>
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

int				g_err;

void	exec_cmd(t_list	*cmd);
void	ft_pipe(t_list **token, t_list **cmp);
char	*ft_find_env(t_list *lst, char	*name);
void	sort_and_print_env(char **envp);
int		no_equal(char *str);
int		launch_bash(t_list	*cmd);
void	prompt(t_list *lst);
void	print_err_code(t_list	*cmd);
void	sig_handler(const int sig);
int		ft_get_path_with_env(t_list *env, t_list *cmd, char **exec_cmd);

char	*get_cmd(char **path, char *cmd, char *path_cmd);
char	*ft_get_env_without(char *str);
char	*ft_get_env(char *str, t_list **list);
void	list_push(t_list **lst_addr, void *data);
void	ft_fill_basic_env(char **env, t_list **lst);
void	ft_check_env(char **env, t_list **lst);
size_t	ft_strlen_double(char **str);

int		ft_get_path(t_list *cmd, char **exec_cmd);
void	ft_check_signal(int pid);

void	ft_print_env(t_list **lst);
void	ft_update_env(char **env, char *name);

void	ft_exit(int status);
void	exit_failure(const char *msg);
void	*ft_malloc(size_t size);
void	ft_free(void *addr);
void	clear_memory(void);

#endif
