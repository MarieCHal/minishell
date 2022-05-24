/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:47:50 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/19 13:24:58 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks the lenght of the dollar variable
int check_dollar_lenght(int i, char *line)
{
    int j;
    
    j = 0;
    i++;
    while ((line[i] != '\0') && (line[i] != '\'') && (line[i] != '\"') && (line[i] != ' ' && (line[i] != '$')))
    {
        i++;
        j++;
    }
    return(j);
}

//replace the $variable per its value
char *check_dollar(int i, char *line)
{
   char *value;
   char *variable;
   int  j;

   j = 0;
   variable = malloc(sizeof(char) * check_dollar_lenght(i, line) + 1);
   i++;
   while ((line[i] != '\0') && (line[i] != '\'') && (line[i] != '\"') && (line[i] != ' ' && (line[i] != '$')))
   {
       variable[j] = line[i];
       j++;
       i++;
   }
   variable[j] = '\0';
   value = get_variable_value(variable);
   free(variable);
   return (value);
}

//checks the quotes and direct to the dollar function depending on th settings
char    *check_quotes(char *line)
{
    char *new_line;
    char *tmp;
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    new_line = malloc(sizeof(char) * 100);
    while (line[i] != '\0')
    {
        if(line[i] == '\'')
        {
            i++;
            while (line[i] != '\'')
            {
                new_line[j] = line[i];
                j++;
                i++;
            }
            i++;
        }
        if (line[i] == '\"')
        {
            i++;
            while (line[i] != '\"')
            {
                if (line[i] == '$')
                {
                    if (check_dollar_lenght(i, line) > 0)
                    {
                        k = 0;
                        tmp = check_dollar(i, line);
                        if (tmp != NULL)
                        {
                            while (tmp[k] != '\0')
                            {
                                new_line[j] = tmp[k];
                                j++;
                                k++;
                            }
                        }
                        i += check_dollar_lenght(i, line);
                        i++;
                    }
                    else
                    {
                        new_line[j] = line[i];
                        i++;
                        j++;
                    }
                }
                else if ((line[i] != '$') && (line[i] != '\"') && (line[i] != '\0'))
                {
                    new_line[j] = line[i];
                    i++;
                    j++;
                }
            }
            i++;
        }
        if ((line[i] != '\'') && (line[i] != '\"') && (line[i] != '\0'))
        {
            if (line[i] == '$' && check_dollar_lenght(i, line) > 0)
            {
                k = 0;
                tmp = check_dollar(i, line);
                if (tmp != NULL)
                {
                    while (tmp[k] != '\0')
                    {
                        new_line[j] = tmp[k];
                        j++;
                        k++;
                    }
                }
                i += check_dollar_lenght(i, line);
                i++;
            }
            else
            {
                new_line[j] = line[i];
                j++;
                i++;
            }
        }
    }
    new_line[j] = '\0';
    return(new_line);
}