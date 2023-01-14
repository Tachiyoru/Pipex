/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:02:34 by sleon             #+#    #+#             */
/*   Updated: 2023/01/14 11:28:41 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_fd(t_pipex *pipex)
{
	if (pipex->fd[IN] != STDIN_FILENO)
	{
		dup2(pipex->fd[IN], STDIN_FILENO);
		close(pipex->fd[IN]);
	}
	if (pipex->fd[OUT] != STDOUT_FILENO)
	{
		dup2(pipex->fd[OUT], STDOUT_FILENO);
		close(pipex->fd[OUT]);
	}
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
