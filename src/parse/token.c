/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:36:48 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/24 20:05:16 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_type	get_type(char *word)
{
	if (word[0] == '|')
		return (PIPE);
	else if (word[0] == '>' && word[1] == '>')
		return (APPEND);
	else if (word[0] == '<' && word[1] == '<')
		return (HEREDOC);
	else if (word[0] == '>')
		return (REDIR_OUT);
	else if (word[0] == '<')
		return (REDIR_IN);
	else if (word[0] == '"' && ft_strchr(word + 1, '"') || 
		word[0] == '\'' && ft_strchr(word + 1, '\'')
		|| word[0] != '"' || word[0] != '\'')
		return (ARG);
	else
		return (NONE);
}

int	get_len(char *word, t_type type)
{
	int len = 0;

	if (type == PIPE || type == REDIR_OUT || type == REDIR_IN)
		return (1);
	else if (type == APPEND || type == HEREDOC)
		return (2);
	else
	{
		if (word[0] == '"')
			len = strcspn(word + 1, "\"");
		else if (word[0] == '\'')
			len = strcspn(word + 1, "'");
		else
			len = strcspn(word, "|>< \t");
		return (len);
	}
}