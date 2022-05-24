/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchalard <mchalard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:41:17 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/20 19:06:16 by mchalard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_variable_value(char *variable)
{
    char *value;

    value = getenv(variable);
    return(value);    
}

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

char    *manage_dollar(t_count *count, char *result, char *line)
{
    char    *tmp;
    
    count->k = 0;
    tmp = check_dollar(count->i, line);
    if (tmp != NULL)
    {
        while (tmp[count->k] != '\0')
        {
            result[count->j] = tmp[count->k];
            count->j++;
            count->k++;
        }
    }
    count->i += check_dollar_lenght(count->i, line);
    count->i++;
    return(result);
}