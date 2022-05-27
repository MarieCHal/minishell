/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeauman <gbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by mchalard          #+#    #+#             */
/*   Updated: 2022/05/19 16:06:19 by gbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd()
{
	char *pwd;
	char *result;

	pwd = NULL;
	result = getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	return (result);
}

char	*ft_just_pwd()
{
	char *pwd;
	char *result;

	pwd = NULL;
	result = getcwd(pwd, sizeof(pwd));
	return (result);
}
