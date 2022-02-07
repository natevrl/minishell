/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:05:17 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/07 14:46:24 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_MINISHELL_H
# define PARSING_MINISHELL_H

# include <minishell.h>
# include <libft.h>

enum {
	LITERAL,
	SP,
	EXIT,
	EXIT_CODE,
	NUM,
	DOLLAR,
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

void	parse_cmd(char *cmd);
void	ft_tokenize_input(t_list **token);

#endif
