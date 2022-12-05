/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:06:40 by sleon             #+#    #+#             */
/*   Updated: 2022/12/05 13:48:34 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (!is_argc_ok(argc, argv[1]))
		return (EXIT_FAILURE);
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

	start = pipex;
	while (pipex)
	{
		sub_exec(pipex);
		if (pipex->type_redir == HEREDOC)
			pipex = pipex->next;
		exec(pipex);
		close(pipex->fd[IN]);
		close(pipex->fd[OUT]);
		pipex = pipex->next;
	}
	pipex = start;
	while (pipex)
	{
		waitpid(pipex->pid, NULL, 0);
		pipex = pipex->next;
	}
}

void	sub_exec(t_pipex *pipex)
{
	int		tmp_pipe[MAX_FD];

	if (pipex->type_redir != DEFAULT)
		setup_redir(pipex);
	if (pipex->type_redir == HEREDOC)
	{
		pipex->next->fd[IN] = pipex->fd[IN];
		pipex = pipex->next;
		setup_redir(pipex);
	}
	if (pipex->next)
	{
		pipe(tmp_pipe);
		pipex->fd[OUT] = tmp_pipe[OUT];
		pipex->next->fd[IN] = tmp_pipe[IN];
	}
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
		if (pipex->cmd == NULL)
			return (msg("Execve failed, bad address"), false);
		else
			execve(pipex->cmd, pipex->cmd_detail, pipex->env);
		dprintf(STDERR_FILENO, "oui");
	}
	return (true);
}
