/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:48:44 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/17 14:45:06 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline/readline.h"
# include "readline/history.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

pid_t   pid_kill;

//parsing malloc
typedef struct s_count
{
    int i;
    int j;
    int k;
    char    *new_line;
}               t_count;

typedef struct s_pid
{
    pid_t     pid_child1;
    pid_t     pid_child2;   
}               t_pid;

typedef struct  s_fd
{
    int red;
    int fd_in;
    int fd_out;
    int heredocs;
    int append;
    char    **tab_in;
}               t_fd;

int     main(void);
//parsing ------------------------------------------
int     ft_quotes(const char *str, int i, char q);
int     ft_count_quotes(const char *str, int i, char q);
int     ft_count_red(char **str, char q);
int	    count_words_red(char **str, char c1, char c2);
int     ft_len_red(char *str, int start);
char    **ft_parse_red(char **tab);
char	*ft_strncpy_red(char *str, int start, int end);
char    *get_variable_value(char *variable);
char    *check_quotes(char *line);
char    **parsed_tab(char *tab, t_fd *files);
int     check_dollar_lenght(int i, char *line);
char    *manage_dollar(t_count *count, char *result, char *line);
char    *check_dollar(int i, char *line);
int     mem_no_quotes(char *line, int pos);
int     mem_double_quotes(char *line, int pos);
int     mem_single_quote(char *line, int pos);
char    **post_red(char **tab);
char    **replace_quotes(char **tab);

//utils----------------------------------------------
size_t	ft_strlen(const char *s);
char    **ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_line(char *s1, char *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_tab(char **tab_to_free);
int	    count_words(const char *str, char c);
char	*word_dup(const char *str, int start, int finish);
char	*copy_new_line(char *new_line);
char	*ft_strncpy(char *str, int start, int end);

//execution------------------------------------------
void    check_exec(char *command);
int     check_cmd(char **tab);
int     built_in(char *command);
char    *get_pwd();
int     check_our_built_in(char **tab);
//int     ft_execve(char *input);
int     ft_execve(char **input);
int     ft_pipe(char **cmd, int nb_pipe);
void	pipe_tab(char *cmd_line);

//int ft_new_execve(char **input);

//built in ------------------------------------------
void	ft_pwd();
void    ft_echo(char **tab);
void    ft_exit();
void    ft_cd(char *path);

//signals-------------------------------------------
void    sig_int();
void    wait_signal();
void    sig_segv();
int     sig_trigger(char c);

void	execute_read();

//redirections-------------------------------------
int     ft_check_fd_in(char **tab, t_fd *files);
int     check_file_in(char *file_name, t_fd *files);
void    check_heredoc(char *key_word, t_fd *files);
int     check_file_out(char *file_name, t_fd *files, int append);
void    close_fd(t_fd *files);
int     ft_len_post_red(char **tab);
int     exec_red(char **cmd, t_fd *files);
int     error_red(char *cmd, t_fd *files);
void    ft_init_red(t_fd *files);
void    close_pipes(int nb_pipe, int fd[nb_pipe][2]);

#endif