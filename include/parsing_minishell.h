/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:05:17 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/06 16:58:04 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_MINISHELL_H
# define PARSING_MINISHELL_H

# include <minishell.h>

enum {
	LITERAL,
	NUM,
	RD_I,
	RD_O,
	AND,
};


typedef struct s_assemble_token {
	int		token;
	char	c;
}				t_atoken;

typedef struct s_token {
	int				token;
	char			c;
	struct s_token	*next;
}				t_token;

t_token	*ft_lstlast_token(t_token *lst);
t_token	*ft_lstnew_token(char c);
void	ft_lstadd_back_token(t_token **alst, t_token *new);
void	parse_cmd(char *cmd);

#endif
