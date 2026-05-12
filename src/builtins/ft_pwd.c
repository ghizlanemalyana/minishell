/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:15:56 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/14 04:42:16 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_shell *sh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		pwd = get_env(sh->hidden_env, "PWD");
		if (pwd == NULL)
			return (perror("pwd"), FAILURE);
		pwd = ft_strdup(pwd);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
