#include "minishell.h"

int main(void)
{
    //t_fd    files;
    char    *cmd;
    char    **split_pipe;
    //char    **split_space1;
    //char    **split_red;
    //char    **post_fd;
    int     j;
    
    j = 0;
    /*files.append = 0;
    files.fd_in = 0;
    files.fd_out = 0;
    files.heredocs = 0;*/
    cmd = "echo salut | grep salut\0";
    split_pipe = ft_split(cmd, '|');
    while (split_pipe[j])
    {
        printf("split_pipe: %s\n", split_pipe[j]);
        j++;
    }
    check_cmd(split_pipe);
    /*printf("split_pipe0[0]: %s\n", split_pipe[0]);
    split_space1 = ft_split(split_pipe[0], ' ');
    while (split_space1[j])
    {
        printf("split_spacce1: %s\n", split_space1[j]);
        j++;
    }
    j = 0;
    split_red = ft_parse_red(split_space1);
    //split_red = parsed_tab(split_space1);
    while (split_red[j])
    {
        printf("split_red: %s\n" , split_red[j]);
        j++;
    }
    ft_check_fd_in(split_red, &files);
    post_fd = post_red(split_red);
    j = 0;
    while (post_fd[j])
    {
        printf("post_red: %s\n", post_fd[j]);
        j++;
    }
    test_red(post_fd, &files);
    //ft_treat_heredoc(post_fd, &files);*/
    return(0);
}