/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:21:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/08 12:49:34 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
}
/*
*/
int main(int ac, char **av, char **envp)
{
	t_shell	sh;

	if (ac != 1)
		return (printf("Usage: ./minishell\n"), FAILURE);
	ft_memset(&sh, 0, sizeof(t_shell));
	if (init_env(&sh.env, envp) == FAILURE)
		return (FAILURE);
	while (1)
	{
		parse(&sh);
		init_cmd(&sh);
		ft_lstclear(&sh.tokens, free);
		//exec(&sh);
	}
}
// while (1)
// {
// 	kanbgheeek
// 	kantsta 3lik
// 	kanmout 3lik
// 	kanbgheeek
// 	kan3ch9ek
// 	nti 7yati
// 	nti chrikti
// 	Kanmout 3lik
// }

