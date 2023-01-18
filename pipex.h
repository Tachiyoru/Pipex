/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:47:09 by sleon             #+#    #+#             */
/*   Updated: 2023/01/18 17:15:33 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "GNL/get_next_line.h"
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
	int		cmdpath;
	int		heredoc;
	char	*path;
	char	*cmd;
	char	**cmd_detail;
	char	**env;
	char	*redir;
	t_fd	type_redir;
	t_pipex	*next;
};

//utils3
void		set_tmp(t_pipex *tmp);
char		*ft_find_path(char **envp);
char		**ft_split2(char	*str, char set);

//utils
int			ft_strncmp(const char *a, const char *b, size_t l);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *str);
void		msg(char *str);

//utils2
int			ft_strcmp(const char *a, const char *b1);
void		pipex_fd(t_pipex *pipex);
char		*path_finder(char **envp);
char		*command_finder(char **path, char *command);
char		*ft_strdup(char *s);

//here-doc
int			setup_redir2(t_pipex *pipex, int fd);
int			is_argc_ok(int argc, char *argv);
int			is_argc_ok1(int argc);
int			heredoc(char *limiter);

//split
char		*ft_putword(char *str, char *tab, char set, int pos);
int			char_count(char *str, char set, int pos);
int			word_count(char *str, char set);
char		**ft_split(char	*str, char set);
void		*ft_memset(void *a, int i, size_t count);

//free
void		free_struct(t_pipex *pipex);
void		ft_free(void *addr);
void		free_tab(char **tab);

//main
int			main(int argc, char **argv, char **envp);
void		main_exec(t_pipex *pipex);
int			sub_exec(t_pipex *pipex);
int			setup_redir(t_pipex *pipex);
int			exec(t_pipex *pipex, t_pipex *start);

//struct
int			fill_strct(t_pipex **pipex, int ac, char **argv, char **envp);
void		ft_lst(t_pipex **node, t_pipex *tmp, int i);
int			init_struct2(t_pipex **node, char **envp, char *cmd, char *lim);
int			init_struct(t_pipex **prev, char **envp, char *cmd, int i);

#endif
