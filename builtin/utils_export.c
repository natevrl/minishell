/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:32:04 by nabentay          #+#    #+#             */
/*   Updated: 2022/02/16 11:35:26 by nabentay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char **envp_copy(char **envp, int max)
{
	char **tab;
	int i;

	tab = malloc(sizeof(char **) * max);
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
	int y;
	int i;
	int max;
	char **tab;

	while (envp[max] != NULL)
		max++;
	tab = envp_copy(envp, max);
	i = 0;
	while (i < max)
	{
		y = i + 1;
		while (y < max)
		{
			if (ft_strncmp(tab[i], tab[y], 1000) > 0)
				str_swap(&tab[i], &tab[y]);
			y++;
		}
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}
