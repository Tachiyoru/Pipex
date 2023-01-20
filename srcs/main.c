/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:06:40 by sleon             #+#    #+#             */
/*   Updated: 2023/01/19 12:34:16 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		fd;

	if (!is_argc_ok1(argc))
		return (EXIT_FAILURE);
	fd = 0;
	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (msg("Could not open out"), 0);
	else
		close(fd);
	if (!fill_strct(&pipex, argc - 2, ++argv, envp))
	{
		free_struct(pipex);
		return (EXIT_FAILURE);
	}
	main_exec(pipex);
	free_struct(pipex);
	return (EXIT_SUCCESS);
}

void	main_exec(t_pipex *pipex)
{
	t_pipex	*start;
	int		i;

	i = 0;
	start = pipex;
	while (pipex)
	{
		if (!sub_exec(pipex))
			return ;
		if (pipex->type_redir == HEREDOC)
			pipex = pipex->next;
		exec(pipex, start);
		close(pipex->fd[IN]);
		close(pipex->fd[OUT]);
		pipex = pipex->next;
		i++;
	}
	pipex = start;
	while (pipex)
	{
		waitpid(pipex->pid, NULL, 0);
		pipex = pipex->next;
	}
}

int	sub_exec(t_pipex *pipex)
{
	int		tmp_pipe[MAX_FD];

	if (pipex->type_redir != DEFAULT)
	{
		if (!setup_redir(pipex))
			return (msg("Could not open fd"), 0);
	}
	if (pipex->type_redir == HEREDOC)
	{
		pipex->next->fd[IN] = pipex->fd[IN];
		pipex = pipex->next;
		if (!setup_redir(pipex))
			return (msg("Could not open fd"), 0);
	}
	if (pipex->next)
	{
		pipe(tmp_pipe);
		pipex->fd[OUT] = tmp_pipe[OUT];
		pipex->next->fd[IN] = tmp_pipe[IN];
	}
	return (1);
}

int	setup_redir(t_pipex *pipex)
{
	int	fd;

	fd = 0;
	if (pipex->type_redir == IN)
	{
		fd = open(pipex->redir, O_RDONLY);
		if (fd == -1)
			return (false);
		pipex->fd[IN] = fd;
		pipex->heredoc = 0;
	}
	else if (pipex->type_redir == OUT)
	{
		if (!setup_redir2(pipex, fd))
			return (false);
	}
	else if (pipex->type_redir == HEREDOC)
	{
		fd = heredoc(pipex->redir);
		pipex->fd[IN] = fd;
	}
	return (true);
}

int	exec(t_pipex *pipex, t_pipex *start)
{
	pid_t			pid;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid > 0)
		pipex->pid = pid;
	else
	{
		pipex_fd(pipex);
		if (pipex->next && pipex->next->fd[IN] != STDIN_FILENO)
			close(pipex->next->fd[IN]);
		if (!ft_strncmp("", pipex->cmd, 1) || access(pipex->cmd_detail[0], 0) != 0)
		{
			close(pipex->fd[IN]);
			close(pipex->fd[OUT]);
			free_struct(start);
			msg("Execve failed, bad address");
			exit(1);
		}
		else
			execve(pipex->cmd, pipex->cmd_detail, pipex->env);
	}
	return (true);
}
