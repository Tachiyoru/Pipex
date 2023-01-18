/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:03:23 by sleon             #+#    #+#             */
/*   Updated: 2023/01/18 17:12:39 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	fill_strct(t_pipex **pipex, int ac, char **argv, char **envp)
{
	t_pipex	*start;
	int		i;

	i = 1;
	if (!ft_strncmp("here_doc", argv[0], 9))
		init_struct2(pipex, envp, argv[0], argv[1]);
	else
		init_struct(pipex, envp, argv[i], 1);
	start = *pipex;
	while (++i < ac)
	{
		init_struct(pipex, envp, argv[i], i);
		if ((i == 2 && start->type_redir != HEREDOC))
		{
			(*pipex)->redir = argv[0];
			(*pipex)->type_redir = IN;
		}
		*pipex = (*pipex)->next;
	}
	(*pipex)->redir = argv[i];
	(*pipex)->type_redir = OUT;
	if (start->heredoc == 1)
		(*pipex)->heredoc = 1;
	*pipex = start;
	return (true);
}

void	init_struct3(t_pipex *tmp, char **res_split)
{
	if ((access(tmp->cmd, 0) != 0 || !strchr(tmp->cmd, '/')) && res_split)
	{
		tmp->cmd = command_finder(res_split, tmp->cmd_detail[0]);
	}
	else
		tmp->cmdpath = 1;
	if (tmp->cmd != NULL)
	{
		free(tmp->cmd_detail[0]);
		tmp->cmd_detail[0] = ft_strdup(tmp->cmd);
	}
}

int	init_struct(t_pipex **node, char **envp, char *cmd, int i)
{
	t_pipex	*tmp;
	char	**res_split;

	tmp = ft_calloc(1, sizeof(t_pipex));
	if (!tmp)
		return (false);
	tmp->cmd = cmd;
	tmp->env = envp;
	set_tmp(tmp);
	tmp->cmd_detail = ft_split(tmp->cmd, ' ');
	if (!ft_strchr(tmp->cmd, '/'))
	{
		res_split = ft_split2(ft_find_path(tmp->env), ':');
		if (ft_strncmp("", cmd, 1))
			init_struct3(tmp, res_split);
		if (res_split)
			free_tab(res_split);
	}
	else
		tmp->cmdpath = 1;
	ft_lst(node, tmp, i);
	return (true);
}

void	ft_lst(t_pipex **node, t_pipex *tmp, int i)
{
	if (i != 1)
		(*node)->next = tmp;
	else
		(*node) = tmp;
}

int	init_struct2(t_pipex **node, char **envp, char *cmd, char *lim)
{
	t_pipex	*tmp;

	tmp = ft_calloc(1, sizeof(t_pipex));
	if (!tmp)
		return (false);
	tmp->cmd = cmd;
	tmp->env = envp;
	tmp->pid = -1;
	tmp->heredoc = 1;
	tmp->fd[IN] = 0;
	tmp->fd[OUT] = 1;
	tmp->redir = lim;
	tmp->type_redir = HEREDOC;
	tmp->cmd_detail = NULL;
	(*node) = tmp;
	return (true);
}
