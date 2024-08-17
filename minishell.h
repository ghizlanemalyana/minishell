/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:37:40 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/15 16:04:04 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>

typedef struct s_lexer
{
	char 			*str;
	t_token			token;
	struct s_lexer 	*next;
	struct s_lexer 	*prev;
} t_lexer;

typedef struct s_token
{
	
} t_token;

typedef struct s_cmd_befor_after_pipe
{
	char 						**str;
	char 						*builting;//(should be a functon pointer to check the cmd used)
									// we have to pase the first word of command to a function
									// this function will loops through a static array of the different builtin function
	// int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	t_lexer						*redirection;
	struct s_cmd_befor_pipe 	*next;
	struct s_cmd_befor_pipe 	*prev;
} t_cmd_befor_pipe;
# endif
