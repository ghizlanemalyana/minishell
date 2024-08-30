/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:06:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/29 21:08:58 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse(t_shell *sh)
{
	t_list	*node;
	t_token	*token;

	node = sh->tokens;
	while (node)
	{
		token = node->content;
		if (token->type == PIPE)
			printf("PIPE\n");
		else if (token->type == ARG)
			printf("ARG\n");
		else if (token->type == REDIR_OUT)
			printf("REDIR_OUT\n");
		else if (token->type == REDIR_IN)
			printf("REDIR_IN\n");
		else if (token->type == APPEND)
			printf("APPEND\n");
		else if (token->type == HEREDOC)
			printf("HEREDOC\n");
		node = node->next;
	}
}
