/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:43:57 by asauvage          #+#    #+#             */
/*   Updated: 2025/12/28 16:01:31 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*tmp_node;

	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	tmp_node = ft_lstlast(*lst);
	tmp_node->next = new_node;
}
