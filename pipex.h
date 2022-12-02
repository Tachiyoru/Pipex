/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:47:09 by sleon             #+#    #+#             */
/*   Updated: 2022/12/02 11:35:04 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_pipex		t_pipex;
typedef enum e_fd			t_fd;

enum e_fd{
	DEFAULT = -1,
	IN,
	OUT,
	MAX_FD,
	HEREDOC,
};

struct s_pipex
{
	pid_t	pid;
	int		fd[MAX_FD];
	char	*path;
	char	*cmd;
	char	**cmd_detail;
	char	**env;
	char	*redir;
	t_fd	type_redir;
	t_pipex	*next;
};

//utils
int			ft_strncmp(const char *a, const char *b, size_t l);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *str);
void		msg(char *str);

//utils2
char		*path_finder(char **envp);
char		*command_finder(char **path, char *command);
char		*ft_strdup(char *s);

//here-doc
int			is_argc_ok(int argc, char *argv);
int			heredoc(char *limiter);

//split
char		**ft_split(char	*str, char set);
void		*ft_memset(void *a, int i, size_t count);

//free
void		free_struct(t_pipex *pipex);
void		ft_free(void *addr);
void		free_tab(char **tab);

//main
int			main(int argc, char **argv, char **envp);
void		main_exec(t_pipex *pipex);
void		sub_exec(t_pipex *pipex);
void		setup_redir(t_pipex *pipex);
int			exec(t_pipex *pipex);

//struct
int			fill_strct(t_pipex **pipex, int ac, char **argv, char **envp);
int			init_struct2(t_pipex **node, char **envp, char *cmd, char *lim);
int			init_struct(t_pipex **prev, char **envp, char *cmd, int i);

#endif
