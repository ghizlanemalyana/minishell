/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:05:12 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/08 18:36:43 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_redirs(t_cmd *redirs)
{
	t_list *redir;
	
	redirs = ft_lstnew(redir);
}

int	set_argv(t_list *tokens, t_cmd *cmd)
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
			tokens = tokens->next;
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
		if (set_argv(tokens, cmd) == FAILURE)
		{
			destory_cmd(cmd);
			return (FAILURE);
		}
		node = ft_lstnew(cmd);
		ft_lstadd_back(&sh->cmds, node);
		while (tokens != NULL && ((t_token *)tokens->content)->type != PIPE)
			tokens = tokens->next;
		if (tokens != NULL)
			tokens = tokens->next;
	}
	display_cmds(sh->cmds);
	return (SUCCESS);
}
