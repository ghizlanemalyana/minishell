/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:05:12 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/11 19:43:43 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_redir(t_cmd *cmd, t_list *token)
{
	t_list	*new;
	t_redir	*redir;

	redir = ft_calloc(sizeof(t_redir), 1);
	if (redir == NULL)
		return (FAILURE);
	redir->type = ((t_token *)token->content)->type;
	if (((t_token *)token->next->content)->content != NULL)
	{
		redir->filename = ft_strdup(((t_token *)token->next->content)->content);
		if (redir->filename == NULL)
		{
			free(redir);
			return (FAILURE);
		}
	}
	new = ft_lstnew(redir);
	if (new == NULL)
	{
		free(redir);
		return(FAILURE);
	}
	ft_lstadd_back(&cmd, new);
	return (SUCCESS);
}

int	set_cmd(t_list *tokens, t_cmd *cmd)
{
	t_token	*token;
	int		i;

	i = 0;
	cmd->argv = ft_calloc(sizeof(char *) , (cmd->argc + 1));
	if (cmd->argv == NULL)
		return (FAILURE);
	while (tokens != NULL)
	{
		token = tokens->content;
		if (isredir(token))
		{
			init_redir(cmd, tokens);
			tokens = tokens->next;
		}
		else if (token->type == ARG)
		{
			cmd->argv[i] = ft_strdup(token->content);
			if (cmd->argv[i] == NULL)
				return (FAILURE);
			i++;
		}
		else
			break;
		tokens = tokens->next;
	}
	return (SUCCESS);
}

int	count_argc(t_list *tokens)
{
	int		counter = 0;
	t_token	*token;

	while (tokens != NULL)
	{
		token = tokens->content;
		if (isredir(token))
			tokens = tokens->next;
		else if (token->type == ARG)
			counter++;
		else
			break ;
		tokens = tokens->next;
	}
	return(counter);
}

void	destory_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->argv != NULL)
	{
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
	}
	free(cmd->argv);
	free(cmd);
}

int init_cmd(t_shell *sh)
{
	t_cmd	*cmd;
	t_list	*node;
	t_list	*tokens;

	tokens = sh->tokens;
	while (tokens != NULL)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (cmd == NULL)
			return (FAILURE);
		cmd->argc = count_argc(tokens);
		if (set_cmd(tokens, cmd) == FAILURE)
			return (destory_cmd(cmd), FAILURE);
		node = ft_lstnew(cmd);
		if (node == NULL)
			return (destory_cmd(cmd), FAILURE);
		ft_lstadd_back(&sh->cmds, node);
		while (tokens != NULL && ((t_token *)tokens->content)->type != PIPE)
			tokens = tokens->next;
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (SUCCESS);
}
