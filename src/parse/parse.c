/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:06:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/08 13:37:47 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_f(char *s1, char *s2, int to_free)
{
	char	*ptr;

	ptr = ft_strjoin(s1, s2);
	if (to_free == 1)
		free(s1);
	else if (to_free == 2)
		free(s2);
	else if (to_free == 3)
	{
		free(s1);
		free(s2);
	}
	return (ptr);
}

/*
	Expansion
	// int i = 0;
	// if (token->content[i] != '$')
	// 	i++;
	// while (token->content[i] == ' ' || token->content[i] == '\t')
	// 	i++;
	// if (token->content[0] == '$')
	// {
	// 	value = get_env(sh->env, token->content + 1);
	// 	if (value == NULL)
	// 		token->content = ft_strdup("");
	// 	else
	// 		token->content = ft_strdup(value);
	// }
*/

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
	else if (word[0] == '"' && ft_strchr(word + 1, '"')
		|| word[0] == '\'' && ft_strchr(word + 1, '\'')
		|| (word[0] != '"' && word[0] != '\''))
		return (ARG);
	else
		return (NONE);
}

//TODO to be updated later
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
		else if (word[0] == '$')
		{
			if (word[1] == '?')
				return (2);
			len = 1;
			while (ft_isalnum(word[len]) || word[len] == '_')
				len++;
		}
		else
			len = strcspn(word, "|>< \t\"'$");
		return (len);
	}
}

int	add_token(t_shell *sh, t_token *new)
{
	t_list	*node;
	char	*tmp;
	t_token	*last;

	if (sh->tokens != NULL)
	{
		last = ft_lstlast(sh->tokens)->content;
		if (last->linked == true)
		{
			last->content = ft_strjoin_f(last->content, new->content, 1);
			last->linked = new->linked;
			free_token(new);
			return (SUCCESS);
		}
	}
	node = ft_lstnew(new);
	ft_lstadd_back(&sh->tokens, node);
	return(SUCCESS);
}

int create_token(t_shell *sh, char *line, int *i)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (FAILURE);
	token->type = get_type(&line[*i]);
	if (token->type == NONE)
		return (free_token(token), ERROR);
	token->len = get_len(&line[*i], token->type);
	if (token->type == NONE)
		return (FAILURE);
	if (token->type == ARG)
	{
		token->quoted = (line[*i] == '"' || line[*i] == '\'');
		if (ft_strchr("|><\t ", *(&line[*i] + token->len + (2 * (token->quoted)))) == NULL)
			token->linked = true;
		token->content = ft_substr(line, *i + token->quoted, token->len);
		if (token->content == NULL)
			return (free_token(token), FAILURE);
	}
	*i += token->len + 2 * token->quoted;
	add_token(sh, token);
	return (SUCCESS);
}

int	parse(t_shell *sh)
{
	char	*line;
	int		i;

	i = 0;
	line = readline(PROMPT);
	if (line == NULL)
		exit(0);
	while (line[i] && line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		if (create_token(sh, line, &i) != SUCCESS)
			exit(1);
		while (line[i] && line[i] == ' ' || line[i] == '\t')
			i++;
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	//print_tokens(sh->tokens);
	free(line);
	return (SUCCESS);
}
