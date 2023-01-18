/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:21:34 by sleon             #+#    #+#             */
/*   Updated: 2023/01/18 17:07:54 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_tmp(t_pipex *tmp)
{
	tmp->cmdpath = 0;
	tmp->pid = -1;
	tmp->heredoc = 0;
	tmp->fd[IN] = 0;
	tmp->fd[OUT] = 1;
	tmp->redir = NULL;
	tmp->type_redir = DEFAULT;
}

char	**ft_split2(char	*str, char set)
{
	int		j;
	char	**tab;

	j = 0;
	if (!str)
		return (NULL);
	tab = ft_calloc(sizeof(char *), word_count(str, set) + 1);
	if (!tab)
		return (ft_free(tab), NULL);
	while (j < word_count(str, set))
	{
		tab[j] = ft_calloc(1, char_count(str, set, j) + 1);
		if (!tab[j])
			return (free_tab(tab), NULL);
		tab[j] = ft_putword(str, tab[j], set, j);
		j++;
	}
	tab[j] = 0;
	free(str);
	return (tab);
}
