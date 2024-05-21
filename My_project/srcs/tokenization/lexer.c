/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:24:48 by lebarbos          #+#    #+#             */
/*   Updated: 2024/05/21 19:14:44 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_tokenlist(t_list **tkns)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *tkns;
	while (tmp && tmp->next)
	{
		if (!is_removable(get(tmp->next)->type)
			&& !is_removable(get(tmp)->type))
		{
			next = tmp->next;
			get(tmp)->value = ft_strjoin_mod(get(tmp)->value,
				get(tmp->next)->value);
			remove_node(tkns, next);
		}
		else
			tmp = tmp->next;
	}
	tmp = *tkns;
	while (tmp)
	{
		next = tmp->next;
		if (is_removable(get(tmp)->type))
			remove_node(tkns, tmp);
		tmp = next;
	}
}

void	expander(t_shell *sh, t_list **tokens)
{
	t_list	*tmp;
	t_list	*to_exclude;

	tmp = *tokens;
	while (tmp)
	{
		if (get(tmp)->value[0] == '$' && get(tmp)->state == GENERAL
			&& tmp->next)
		{
			if (get(tmp->next)->type != E_SPACE)
			{
				to_exclude = tmp;
				expand_general(sh, to_exclude);
			}
		}
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (get(tmp)->state == IN_DQUOTES)
			if (get(tmp)->type != HEREDOC)
				expand_quotes(sh, tmp);
		tmp = tmp->next;
	}
}

// void	review_tkn_list(t_list **tkn)
// {
// 	t_list	*tmp;
// 	t_list	*nxt;

// 	tmp = *tkn;
// 	while (tmp && tmp->next)
// 	{
// 		nxt = tmp->next;
// 		if (ft_strcmp(get(tmp)->value, "") == 0
// 			&& !is_removable(get(nxt)->type))
// 		{
// 			get(nxt)->type = get(tmp)->type;
// 			remove_node(tkn, tmp);// Remove o nó atual
// 		}
// 		else if (get(tmp)->type == HEREDOC)
//         {
//             char *joined_value = ft_strdup(get(tmp)->value);
//             t_list *to_remove = nxt;
//             while (to_remove && !is_removable(get(to_remove)->type))
//             {
//                 char *new_joined_value = ft_strjoin(joined_value, get(to_remove)->value);
//                 free(joined_value); // Liberar a string anterior
//                 joined_value = new_joined_value;
//                 to_remove = to_remove->next;
//             }
//             free(get(tmp)->value); // Liberar o valor antigo
//             get(tmp)->value = joined_value; // Atualizar com o novo valor unido

//             // Remover todos os nós subsequentes até encontrar um tipo removível
//             while (nxt && nxt != to_remove)
//             {
//                 t_list *next_nxt = nxt->next;
//                 remove_node(tkn, nxt);
//                 nxt = next_nxt;
//             }
//         }
// 		tmp = nxt;// Avança para o próximo nó
// 	}
// }

// void	review_tkn_list(t_list **tkn)
// {
// 	t_list *tmp;
// 	int		typee;

// 	tmp = *tkn;
// 	while (tmp)
// 	{
// 		typee = get(tmp)->type;
// 		if (typee >= 7)
// 		{
// 			tmp = tmp->next;
// 			while (tmp && get(tmp)->type == 0)
// 			{
// 				get(tmp)->type = typee;
// 				tmp = tmp->next;
// 			}
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// }

// void	review_tkn_list(t_list **tkn)
// {
// 	t_list *tmp;
// 	t_list *heredoc_start;
// 	int		typee;

// 	tmp = *tkn;
// 	while (tmp)
// 	{
// 		typee = get(tmp)->type;
// 		if (typee == HEREDOC)
// 		{
// 			heredoc_start = tmp;
// 			while (tmp && get(tmp)->type != E_SPACE)
// 			{
// 				if (get(tmp)->state == IN_DQUOTES || get(tmp)->state == IN_SQUOTES)
// 				{
// 					int quote_type = get(tmp)->state;
// 					tmp = heredoc_start;
// 					while (tmp && get(tmp)->type != E_SPACE)
// 					{
// 						if (get(tmp)->type == HEREDOC)
// 							get(tmp)->state = quote_type;
// 						tmp = tmp->next;
// 					}
// 					break;
// 				}
// 				tmp = tmp->next;
// 			}
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// }

// void	review_tkn_list(t_list **tkn)
// {
// 	t_list *tmp;
// 	t_list *heredoc_start;
// 	int		typee;

// 	tmp = *tkn;
// 	while (tmp)
// 	{
// 		typee = get(tmp)->type;
// 		if (typee >= 7)
// 		{
// 			// Transformar nós do tipo 0 após um tipo >= 7 para o tipo >= 7
// 			t_list *start = tmp->next;
// 			while (start && get(start)->type == 0)
// 			{
// 				get(start)->type = typee;
// 				start = start->next;
// 			}
// 			// Se o tipo for HEREDOC, realizar a verificação adicional
// 			if (typee == HEREDOC)
// 			{
// 				heredoc_start = tmp;
// 				t_list *inner_tmp = tmp;
// 				while (inner_tmp && get(inner_tmp)->type != E_SPACE)
// 				{
// 					if (get(inner_tmp)->state == IN_DQUOTES || get(inner_tmp)->state == IN_SQUOTES)
// 					{
// 						// int quote_type = get(inner_tmp)->state;
// 						inner_tmp = heredoc_start;
// 						while (inner_tmp && get(inner_tmp)->type != E_SPACE)
// 						{
// 							// if (get(inner_tmp)->type == HEREDOC)
// 							get(inner_tmp)->not_expand = true;
// 							inner_tmp = inner_tmp->next;
// 						}
// 						break;
// 					}
// 					inner_tmp = inner_tmp->next;
// 				}
// 			}
// 			tmp = start;  // Avançar tmp para continuar iterando na lista
// 		}
// 		else
// 		{
// 			tmp = tmp->next;
// 		}
// 	}
// }

void transform_nodes(t_list *start, int type) 
{
	while (start && get(start)->type == 0) 
	{
		get(start)->type = type;
		start = start->next;
	}
}

void handle_heredoc(t_list *start) 
{
	t_list *inner_tmp;
	
	inner_tmp = start;
	while (inner_tmp && get(inner_tmp)->type != E_SPACE) 
	{
		if (get(inner_tmp)->state == IN_DQUOTES
			|| get(inner_tmp)->state == IN_SQUOTES) {
			t_list *heredoc_start = start;
			while (heredoc_start && get(heredoc_start)->type != E_SPACE) 
			{
				get(heredoc_start)->not_expand = true;
				heredoc_start = heredoc_start->next;
			}
			break;
		}
		inner_tmp = inner_tmp->next;
	}
}

// Função principal refatorada
void review_tkn_list(t_list **tkn) 
{
	t_list *tmp;
	int		typee;

	tmp = *tkn;
	while (tmp) 
	{
		typee = get(tmp)->type;
		if (typee >= 7) 
		{
			transform_nodes(tmp->next, typee);
			if (typee == HEREDOC)
				handle_heredoc(tmp);
			tmp = tmp->next;
		} 
		else
			tmp = tmp->next;
	}
}

void	lexer(t_shell *sh, char *input)
{
	fill_token_lst(sh, input); //tokens without state;
	review_tkn_typ(sh->token_lst); // set state
	review_tkn_list(&sh->token_lst);
	expander(sh, &sh->token_lst);
	clean_tokenlist(&sh->token_lst); // join and clean spaces
	print_tokens(sh); // just print
}
