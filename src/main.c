/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:21:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/08 18:51:26 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int main (int ac, char **av, char **envp)
{
	// t_shell	sh;

	// //size_t word_len;
	// char *word;
	// t_list *node;
	// t_token	*token;

	// ft_memset(&sh, 0, sizeof(t_shell));
	// while (1)
	// {
	// 	parse(&sh);
		
	// 	sh.line = readline("minishell$ ");
	// 	int i = 0;
	// 	while (sh.line[i] != '\0')
	// 	{
	// 		token = malloc(sizeof(t_token));
			
	// 		token->type = get_type(&sh.line[i]);
	// 		token->len = get_len(&sh.line[i], token->type);
	// 		// word = ft_substr(sh.line, i, word_len);
	// 		token->content = ft_substr(sh.line, i + (sh.line[i] == '"' || sh.line[i] == '\''), token->len);

	// 		if (token->type == NONE)
	// 			return 0;
	// 		node = ft_lstnew(token);
	// 		ft_lstadd_back(&sh.tokens, node);

	// 		// i = i + word_len;
	// 		i = i + token->len + 2 * (sh.line[i] == '"' || sh.line[i] == '\'');
	// 		while (sh.line[i] && sh.line[i] == ' ')
	// 			i++;
	// 	}
	// 	if (sh.line[0] != '\0')
	// 		add_history(sh.line);
	// }

}