/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:37:40 by sleon             #+#    #+#             */
/*   Updated: 2023/01/17 18:05:27 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_struct(t_pipex *pipex)
{
	t_pipex	*save;

	while (pipex)
	{
		if (pipex->type_redir == HEREDOC)
		{
			save = pipex;
			pipex = pipex->next;
			free(save);
		}
		else
		{
			free_tab(pipex->cmd_detail);
			if (pipex->cmd)
			{
				if (ft_strncmp("", pipex->cmd, 1) && pipex->cmdpath == 0)
					free(pipex->cmd);
			}
			save = pipex;
			pipex = pipex->next;
			free(save);
		}
	}
	free(pipex);
}

void	ft_free(void *addr)
{
	free(addr);
	addr = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}
