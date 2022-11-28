/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:29:07 by sleon             #+#    #+#             */
/*   Updated: 2022/11/28 17:49:20 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../GNL/get_next_line.h"

int	is_heredoc(char *arg, t_pipex *pipex, char **envp)
{
	init_struct(&pipex, envp, arg, 1);
	if (arg && !ft_strncmp("here_doc", arg, 9))
	{
		pipex->heredoc = 1;
		return (6);
	}
	else
	{
		pipex->heredoc = 0;
		return (5);
	}
}

void	heredoc(char *limiter, t_pipex *pipex)
{
	int		file;
	char	*buf;

	file = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		return (msg("error heredoc"));
	while (1)
	{
		write(1, ">", 1);
		buf = get_next_line(0);
		if (buf < 0)
			exit(1);
		if (ft_strncmp(limiter, buf, ft_strlen(limiter) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	pipex->fd[IN] = open("heredoc_tmp", O_RDONLY);
}
