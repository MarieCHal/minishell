/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:48:44 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/29 16:56:14 by mchalard         ###   ########.fr       */
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
#include <termios.h>

extern int g_exit_status;

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
    int       fd[2];   
}               t_pid;

typedef struct  s_fd
{
    int red;
    int fd_in;
    int fd_out;
    int heredocs;
    int append;
    char    **tab_in;
    int     error;
    int     fd[100][2];
    int     pid[100];
    int     nb_pipe;
}               t_fd;

typedef struct s_red
{
    char    **new;
    int     i;
    int     j;
    int     n;
}               t_red;

typedef struct  s_split
{
    size_t	i;
	size_t	j;
	int		index;
	int		check;
}               t_split;

typedef struct s_tab
{
	char	*old_pwd;
	char	*dir;
	char	*pwd_var;
	char	*oldpwd_var;
	char	**envp;
	char	*just_path;
	char	*home_path;
	char	*another_oldpwd;
}			t_tab;

int     main(int argc, char **argv, char **envp);
//parsing ------------------------------------------
int     ft_quotes(const char *str, int i, char q);
int     ft_count_quotes(const char *str, int i, char q);
int     ft_count_red(char **str, char q);
int	    count_words_red(char **str, char c1, char c2);
int     ft_len_red(char *str, int start);
char    **ft_parse_red(char **tab);
char	*ft_strncpy_red(char *str, int start, int end);
char    *get_variable_value(char *variable, t_tab *tab);
char    *check_quotes(char *line, t_tab *tab);
char    **parsed_tab(char *tab, t_fd *files);
int     check_dollar_lenght(int i, char *line);
char    *manage_dollar(t_count *count, char *result, char *line, t_tab *tab);
char    *check_dollar(int i, char *line, t_tab *tab);
int     mem_no_quotes(char *line, int pos, t_tab *tab);
int     mem_double_quotes(char *line, int pos, t_tab *tab);
int     mem_single_quote(char *line, int pos);
char    **post_red(char **tab);
char    **replace_quotes(char **tab, t_tab *tab1);
int     check_error_nb_quotes(char *cmd);
int     ft_count_cmd(char **result, t_tab *tab);
int	    ft_count_pipes(char *cmd_line, char **result);
char	*stock_quotes(t_count *count);

//utils----------------------------------------------
size_t	ft_strlen(const char *s);
char    **ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_line(char *s1, char *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_tab(char **tab_to_free);
void	free_double(char *stock, char *tmp);
int	    count_words(const char *str, char c);
char	*word_dup(const char *str, int start, int finish);
char	*copy_new_line(char *new_line);
char	*ft_strncpy(char *str, int start, int end);
int	    check_cat(char **result);
void    ft_unvalid_cmd(char **cmd_pipe, t_tab *tab);
int	    ft_atoi(char *str);

//execution------------------------------------------
void    check_exec(char *command);
int     check_cmd(char **tab_split, t_tab *tab);
int     built_in(char *command);
int     check_our_built_in(char **tab1, t_tab *tab);
int     ft_execve(char **input, t_tab *tab);
int     ft_pipe(char **cmd, int nb_pipe, int i, t_tab *tab);
int	    ft_wait_pid(t_fd *files);

//signals-------------------------------------------
void    wait_signal();
void    sig_segv();
int     sig_trigger(char c);
void    init_signals(struct termios *sig);
char	*ft_itoa(int n);
void	ft_putendl_fd(char *s, int fd);
void	rl_replace_line (const char *text, int clear_undo);
int	    ft_check_if_child(int new_val);

//redirections-------------------------------------
int     ft_check_fd_in(char **tab, t_fd *files);
int     check_file_in(char *file_name, t_fd *files);
void    check_heredoc(char *key_word, t_fd *files);
int     check_file_out(char *file_name, t_fd *files, int append);
void    close_fd(t_fd *files);
int     ft_len_post_red(char **tab);
int     exec_red(char **cmd, t_fd *files, t_tab *tab);
int     error_red(char **cmd);
void    ft_init_red(t_fd *files);
void	close_pipes(int nb_pipe, int (*fd)[2]);
int     ft_search_red(char **cmd);
int     ft_check_parse_error(char **cmd);


//built in ------------------------------------------
int     ft_echo(char **tab);
int		ft_pwd(t_tab *tab);
int	ft_exit(char **tab);
int	    ft_cd(char *path, t_tab *tab);
int		ft_get_env(t_tab *tab);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	envp_init(t_tab *tab, char **envp);
char	*ft_strdup(const char *s1);
int		ft_export(t_tab *tab, char **var);
int		ft_unset(t_tab *tab, char **var);
void	free_tab(char **tab);
int		check_valid_id(char *var, int i);
int		find_pwd_line(t_tab *tab);
void	ft_is_oldpwd(t_tab *tab, int j);
char	*fill_malloc(t_tab *tab, int j, int i, int len);
void	ft_back_cd(t_tab *tab, char *path, int j, int i);
void	ft_is_back(t_tab *tab, int j);
void	free_envp(t_tab *tab);
char	**envp_cpy(t_tab *tab, char **envp_stock);
void	new_envp(t_tab *tab, char **envp_stock, char *var);
int		check_equal(char *var);
void	ft_init_built_in(t_tab *tab);
void	fill_new_envp(t_tab *tab, char **envp_stock, char *var);
char	*new_path_malloc(char *path, char *new_path);
void	cd_home(t_tab *tab, int j);

#endif