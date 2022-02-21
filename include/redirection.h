/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:23:17 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/21 14:32:10 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <minishell.h>
# include <libft.h>
# include <builtin.h>

void	redirect_out_cmd(t_list	*cmd, int fd);
void	redirect_in_cmd(t_list	*cmd, int fd);
void	redirect_in_cmd2(t_list	*cmd, t_list *arg, int fd);
void	here_doc(char *limiter);

#endif
