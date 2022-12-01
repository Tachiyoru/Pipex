/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:29:07 by sleon             #+#    #+#             */
/*   Updated: 2022/12/01 14:13:12 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../GNL/get_next_line.h"

// int	is_heredoc(char *arg, t_pipex *pipex, char **envp)
// {
// 	if (arg && !ft_strncmp("here_doc", arg, 9))
// 	{
// 		pipex->type_redir = HEREDOC;
// 		return (6);
// 	}
// 	else
// 	{
// 		pipex->heredoc = 0;
// 		return (5);
// 	}
// }

int	heredoc(char *limiter)
{
	int		file;
	char	*buf;
	int		fd;

	file = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		return (-1);
	while (1)
	{
		write(STDIN_FILENO, ">", 1);
		buf = get_next_line(0);
		if (buf < 0)
			break ;
		if (!ft_strncmp(limiter, buf, ft_strlen(limiter)))
			break ;
		write(file, buf, ft_strlen(buf));
		// write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	fd = open(".heredoc_tmp", O_RDONLY);
	return (fd);
}
