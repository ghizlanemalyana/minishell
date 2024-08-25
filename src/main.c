/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:21:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/24 20:13:52 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	func()
// {
// 	t_list	list;
// 	t_list	*ptr;

// 	ptr = ft_lstnew("Ilyasse");
// 	list.content = "Ilyasse";
// 	list.next = NULL;

// }

// ls
int main (int ac, char **av)
{
	t_shell	sh;

	//size_t word_len;
	char *word;
	t_list *node; 

	ft_memset(&sh, 0, sizeof(t_shell));
	while (1)
	{
		if (ac == 1)
			sh.line = readline("minishell$ ");
		else
			sh.line = ft_strdup("\"hii i\"");
		int i = 0;
		while (sh.line[i] != '\0')
		{
			node = ft_lstnew(NULL);

			node->type = get_type(&sh.line[i]);
			
			node->len = get_len(&sh.line[i], node->type);
			
			// word = ft_substr(sh.line, i, word_len);
			node->content = ft_substr(sh.line, i + (sh.line[i] == '"' || sh.line[i] == '\''), node->len);

			if (node->type == NONE)
				return 0;
			printf("%d\n", node->type);
			printf("%s\n", node->content);
			ft_lstadd_back(&sh.tokens, node);

			// i = i + word_len;
			i = i + node->len + 2 * (sh.line[i] == '"' || sh.line[i] == '\'');
			while (sh.line[i] && sh.line[i] == ' ')
				i++;
		}
		if (sh.line[0] != '\0')
			add_history(sh.line);
	}
}
