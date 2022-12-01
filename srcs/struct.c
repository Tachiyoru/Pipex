/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:03:23 by sleon             #+#    #+#             */
/*   Updated: 2022/12/01 13:12:19 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	fill_strct(t_pipex **pipex, int ac, char **argv, char **envp)
{
	t_pipex	*start;
	int		i;

	i = 1;
	if (!ft_strncmp("here_doc", argv[0], 9))
	{
		init_struct2(pipex, envp, argv[0], i);
		(*pipex)->redir = argv[1];
		(*pipex)->type_redir = HEREDOC;
	}
	else
		init_struct(pipex, envp, argv[i], i);
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
		// if (start->type_redir == HEREDOC && i == 2)
		// {
		// 	(*pipex)->redir = argv[ac];
		// 	(*pipex)->type_redir = IN;
		// }
	}
	(*pipex)->redir = argv[i];
	(*pipex)->type_redir = OUT;
	*pipex = start;
	return (true);
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
	tmp->pid = -1;
	tmp->fd[IN] = 0;
	tmp->fd[OUT] = 1;
	tmp->redir = NULL;
	tmp->type_redir = DEFAULT;
	tmp->cmd_detail = ft_split(tmp->cmd, ' ');
	res_split = ft_split(path_finder(tmp->env), ':');
	tmp->cmd = command_finder(res_split, tmp->cmd_detail[0]);
	tmp->cmd_detail[0] = ft_strdup(tmp->cmd);
	free_tab(res_split);
	if (i != 1)
		(*node)->next = tmp;
	else
		(*node) = tmp;
	return (true);
}

int	init_struct2(t_pipex **node, char **envp, char *cmd, int i)
{
	t_pipex	*tmp;
	// char	**res_split;

	tmp = ft_calloc(1, sizeof(t_pipex));
	if (!tmp)
		return (false);
	tmp->cmd = cmd;
	tmp->env = envp;
	tmp->pid = -1;
	tmp->fd[IN] = 0;
	tmp->fd[OUT] = 1;
	tmp->redir = NULL;
	tmp->type_redir = DEFAULT;
	tmp->cmd_detail = NULL;
	// res_split = ft_split(path_finder(tmp->env), ':');
	// tmp->cmd = command_finder(res_split, tmp->cmd_detail[0]);
	// tmp->cmd_detail[0] = ft_strdup(tmp->cmd);
	// free_tab(res_split);
	if (i != 1)
		(*node)->next = tmp;
	else
		(*node) = tmp;
	return (true);
}

char	*path_finder(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*command_finder(char **path, char *command)
{
	char	*tmp;
	char	*cmd;

	while (*path)
	{
		tmp = ft_strjoin (*path, "/");
		cmd = ft_strjoin (tmp, command);
		free(tmp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		path++;
	}
	return (NULL);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;
	int		size;

	size = 0;
	while (s[size])
		size++;
	str = (char *)malloc(sizeof (char) * (size + 1));
	i = 0;
	if (str == 0)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
