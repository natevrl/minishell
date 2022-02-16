/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:05:17 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/16 06:06:13 by nabentay         ###   ########.fr       */
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
	QUOTE,
	DQUOTE,
	EXIT_CODE,
	SP,
	CMD,
	NUM,
	RD_I,
	RD_ID,
	RD_O,
	RD_OA,
	PIPE,
	OR,
	EXEC,
};

typedef struct s_cmd
{
	void			*content;
	struct s_list	*next;
}					t_cmd;

void	parse_cmd(char *cmd, t_list *lst);
void	ft_tokenize_input(t_list **tmp);

char	*ft_before_equal(char *env);
char	*ft_after_equal(char *env);

t_list	*ft_lstnew_token(void	*content, int token);
void	ft_exec_token(t_list **cmd_token);
int		ft_strlen_token(t_list *token);
void	ft_set_option(t_list **tmp);

void	ft_translate_token(t_list **tmp);
void	ft_assemble_token(t_list **cmd_token, t_list **tmp);
void	ft_assemble_dquote(t_list **token, char **cmd, int *i);
void	ft_assemble_exit(t_list **token, char **cmd, int *i);
void	ft_assemble_dollard(t_list **token, char **cmd, int *i);
void	ft_assemble_quote(t_list **token, char **cmd, int *i);

#endif
