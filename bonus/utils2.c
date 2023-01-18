/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:02:34 by sleon             #+#    #+#             */
/*   Updated: 2023/01/18 17:03:53 by sleon            ###   ########.fr       */
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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_find_path(char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strnstr(envp[index], "PATH", 4) != NULL)
			return (ft_strdup(&envp[index][5]));
		index++;
	}
	return (NULL);
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
