/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:05:17 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/11 11:41:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_MINISHELL_H
# define PARSING_MINISHELL_H

# include <minishell.h>
# include <libft.h>

enum {
	LITERAL,
	INTERO,
	DOLLARD,
	EXIT_CODE,
	SP,
	NUM,
	RD_I,
	RD_ID,
	RD_O,
	RD_OA,
	PIPE,
	BG,
	AND,
	OR,
	EXEC,
};

typedef struct s_cmd
{
	void			*content;
	struct s_list	*next;
}					t_cmd;

void	parse_cmd(char *cmd, char **env);
void	ft_tokenize_input(t_list **tmp);

t_list	*ft_lstnew_token(void	*content, int token);
int		ft_strlen_token(t_list *token);
void	ft_set_option(t_list **tmp);

#endif
