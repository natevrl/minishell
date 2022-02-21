/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_minishell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:33:32 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/21 18:18:24 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MINISHELL_H
# define ENV_MINISHELL_H

# include <minishell.h>
# include <libft.h>

void	ft_add_under(char **envp, t_list **list);
void	ft_add_pwd(char **envp, t_list **list);
void	ft_add_shlvl(char **envp, t_list **list);

void	ft_check_required(char **envp, t_list **lst);
void	ft_find_add_env(char **envp, t_list **lst_env, char *name);
int		ft_get_path_with_env_arg(t_list *env, t_list *cmd, char **exec_cmd);
char	*ft_find_env(t_list *lst, char	*name);
int		ft_get_path_with_env(t_list *env, t_list *cmd, char **exec_cmd);
int		ft_get_path(t_list *cmd, char **exec_cmd);

void	sort_and_print_env(char **envp);
int		no_equal(char *str);
void	ft_print_env(t_list **lst);
void	ft_update_env(char **env, char *name);

char	*ft_get_env_without(char *str);
char	*ft_get_env(char *str, t_list **list);
void	ft_fill_basic_env(char **env, t_list **lst);
void	ft_check_env(char **env, t_list **lst);

#endif
