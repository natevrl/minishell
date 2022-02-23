/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:13:28 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/23 17:28:44 by ubuntu           ###   ########.fr       */
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
int		launch_bash(t_list	*cmd);
void	prompt(t_list *lst);

char	*get_cmd(char **path, char *cmd, char *path_cmd);
size_t	ft_strlen_double(char **str);

void	ft_check_signal(int pid);
void	sig_handler(const int sig);

void	list_push(t_list **lst_addr, void *data);
void	ft_exit(int status);
void	exit_failure(const char *msg);
void	*ft_malloc(size_t size);
void	ft_free(void *addr);
void	clear_memory(void);

#endif
