/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:32:04 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/23 14:34:33 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static char	**envp_copy(char **envp, int max)
{
	char	**tab;
	int		i;

	tab = ft_malloc(sizeof(char **) * max);
	i = -1;
	while (envp[++i])
		tab[i] = envp[i];
	return (tab);
}

static void	str_swap(char **s1, char **s2)
{
	char	*tampon;

	tampon = *s1;
	*s1 = *s2;
	*s2 = tampon;
}

void	sort_and_print_env(char **envp)
{
	int		y;
	int		i;
	int		max;
	char	**tab;

	max = 0;
	while (envp[max] != NULL)
		max++;
	tab = envp_copy(envp, max);
	i = 0;
	while (i < max)
	{
		y = i + 1;
		while (y < max)
		{
			if (ft_strncmp(tab[i], tab[y], ft_strlen(tab[i])
					+ ft_strlen(tab[y])) > 0)
				str_swap(&tab[i], &tab[y]);
			y++;
		}
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

void	ft_fill_env(char *arg, t_list *cmd, char **env)
{
	*env = arg;
	((t_myenv *)cmd->content)->env = arg;
	((t_myenv *)cmd->content)->name = ft_before_equal(arg);
	((t_myenv *)cmd->content)->value = ft_after_equal(arg);
}
