/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:06:40 by sleon             #+#    #+#             */
/*   Updated: 2022/12/01 12:33:10 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5)
	{
		msg("Pipex run as: ./pipex infile cmd1 ... cmdX outfile");
		msg("or as : ./pipex here_doc LIMITER cmd cmd1 file");
		return (0);
	}
	if (!fill_strct(&pipex, argc - 2, ++argv, envp))
	{
		free_struct(pipex);
		return (EXIT_FAILURE);
	}
	main_exec(pipex);
	free_struct(pipex);
	dprintf(STDERR_FILENO, "ok\n");
	return (EXIT_SUCCESS);
}

void	main_exec(t_pipex *pipex)
{
	t_pipex	*start;
	int		tmp_pipe[MAX_FD];

	start = pipex;
	while (pipex)
	{
		if (pipex->type_redir != DEFAULT)
			setup_redir(pipex);
		if (pipex->next)
		{
			pipe(tmp_pipe);
			pipex->fd[OUT] = tmp_pipe[OUT];
			pipex->next->fd[IN] = tmp_pipe[IN];
		}
		exec(pipex);
		close(pipex->fd[IN]);
		close(pipex->fd[OUT]);
		pipex = pipex->next;
	}
	pipex = start;
	{
		waitpid(pipex->pid, NULL, 0);
		pipex = pipex->next;
	}
	return ;
}

void	setup_redir(t_pipex *pipex)
{
	int	fd;

	if (pipex->type_redir == IN)
	{
		fd = open(pipex->redir, O_RDONLY);
		if (fd == -1)
			return ;
		pipex->fd[IN] = fd;
	}
	else if (pipex->type_redir == OUT)
	{
		fd = open(pipex->redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return ;
		pipex->fd[OUT] = fd;
	}
	else if (pipex->type_redir == HEREDOC)
	{
		fd = heredoc(pipex->redir);
		pipex->fd[IN] = fd;
	}
	return ;
}

int	exec(t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid > 0)
		pipex->pid = pid;
	else
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
		// dprintf(STDERR_FILENO, "%s\n", pipex->cmd);
		if (pipex->cmd == NULL)
			return (msg("Execve failed"), exit(1), false);
		else
			execve(pipex->cmd, pipex->cmd_detail, pipex->env);
		perror("Error ");
	}
	return (true);
}

// dprintf(STDERR_FILENO, "cmd detail = %s\n", pipex->cmd);
