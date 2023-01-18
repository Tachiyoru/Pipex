/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:29:07 by sleon             #+#    #+#             */
/*   Updated: 2023/01/18 16:59:11 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../GNL/get_next_line.h"

int	is_argc_ok(int argc, char *argv)
{
	if (!ft_strncmp("here_doc", argv, 9) && argc < 6)
	{
		msg("Pipex run as : ./pipex here_doc LIMITER cmd cmd1 file");
		return (0);
	}
	else if (argc < 5)
	{
		msg("Pipex run as: ./pipex infile cmd1 ... cmdX outfile");
		return (0);
	}
	return (1);
}

int	heredoc(char *limiter)
{
	int		file;
	char	*buf;
	int		fd;

	file = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		return (-1);
	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		write(STDIN_FILENO, ">", 1);
		buf = get_next_line(0, 0);
		if (buf < 0)
			break ;
		if (!ft_strncmp(limiter, buf, ft_strlen(limiter)))
			break ;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	get_next_line(0, 1);
	close(file);
	fd = open(".heredoc_tmp", O_RDONLY);
	return (free(limiter), fd);
}

int	setup_redir2(t_pipex *pipex, int fd)
{
	if (pipex->heredoc == 1)
	{
		fd = open(pipex->redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (false);
	}
	else
	{
		fd = open(pipex->redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (false);
	}
	pipex->fd[OUT] = fd;
	return (true);
}
