/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_minishell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:33:32 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/17 16:19:37 by ubuntu           ###   ########.fr       */
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

#endif
