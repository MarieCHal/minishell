/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:43:33 by mchalard          #+#    #+#             */
/*   Updated: 2022/06/16 13:45:34 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns the cmd line parsed without the redirection and stores in struct the stdin and stdout

char    *ft_strncpy(char *cmd, int start, int end)
{
    int i;
    int j;
    char *new;
    
    i = 0;
    j = start;
    if (start == 0)
    {
        new = malloc(sizeof(char) * (end));
        while (i < end)
        {
            new[i] = cmd[i];
            i++;
        }
        new[i] = '\0';
    }
    else if (start > 0)
    {
        new = malloc(sizeof(char) * (ft_strlen(cmd) - start));
        while (cmd[j])
        {
            new[i] = cmd[j];
            i++;
            j++;
        }
        new[i] = '\0';
    }
    return(new);
}

//get the file name
char    *get_file_name(char **cmd_to_parse, int start)
{
    char    *file_name;
    int     i;
    int     j;

    i = start;
    j = 0;
    while (cmd_to_parse[i] != ' ' && cmd_to_parse[i] != '<' && cmd_to_parse[i] != '>' && cmd_to_parse[i] != '\0')
        i++;
    file_name = malloc(sizeof (char) * (i + 1));
    /*i = start;
    while (cmd_to_parse[i] != ' ' && cmd_to_parse[i] != '<' && cmd_to_parse[i] != '>' && cmd_to_parse[i] != '\0')
    {
        file_name = 
    }*/
}

//find red input
int check_red_in(char *cmd)
{
    int i;
    int j;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '\"')
        {
            while (cmd[i] != '\"')
                i++;
            i++;
        }
        if (cmd[i] == '\'')
        {
            while (cmd[i] != '\'')
                i++;
            i++;
        }  
        if (cmd[i] == '<')
            return (i);
        i++;
    }
    return (-1);
}

//returns the line parsed 
char    *replace_cmd_line(char *cmd_to_parse, int i)
{
    int j;
    char    *tmp_beg;
    char    *tmp_end;
    char    *file_name;
    
    j = 0;
    printf("i in replace line: %d\n", i);
    tmp_beg = ft_strncpy(cmd_to_parse, 0, i);
    if (cmd_to_parse[i] == '<')
    {
        while (cmd_to_parse[i] == '<')
        {
            i++;
            j++;
        }
    }
    if (cmd_to_parse[i] == '>')
    {
        while (cmd_to_parse[i] == '>')
        {
            i++;
            j++;
        }
    }
    i++;
    file_name = get_file_name(cmd_to_parse, i);
    while (cmd_to_parse[i] != ' ' && cmd_to_parse[i] != '<' && cmd_to_parse[i] != '>' && cmd_to_parse[i] != '\0')
    {
        i++;
        j++;
    }
    
}

//checks for red input
char    *find_input(char *cmd)
{
    int i;
    int j;
    char    *new_cmd;
    char    *tmp;
    
    i = 0;
    j = 0;
    new_cmd = copy_new_line(cmd);
    while ((i = check_red_in(new_cmd)) != -1)
    {
        tmp = replace_cmd_line(new_cmd, i);
        free(new_cmd);
        new_cmd = copy_new_line(tmp);
        free(tmp);     
    }
    return (new_cmd);
}