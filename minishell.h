/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:37:40 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/30 22:43:23 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <string.h>
#include <errno.h>
# include <readline/readline.h>

typedef enum e_type
{
	NONE,
	PIPE,
	ARG,
	REDIR_OUT,
	REDIR_IN,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_token
{
	char			*content;
	int				len;
	int				type;
}	t_token;

typedef struct s_shell
{
	char			*line;
	t_list			*tokens;
	// t_list			*commands;
}	t_shell;

t_type		get_type(char *word);
int			get_len(char *word, t_type type);

# endif