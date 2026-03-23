/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:17:54 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/18 10:38:28 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*tmp_node;
	void	*tmp_content;

	new_l = 0;
	while (lst != NULL)
	{
		tmp_content = f(lst->content);
		tmp_node = ft_lstnew(tmp_content);
		if (tmp_content == NULL)
		{
			del(tmp_content);
			ft_lstclear(&tmp_node, (*del));
			free(tmp_node);
			return (0);
		}
		ft_lstadd_back(&new_l, tmp_node);
		lst = lst->next;
	}
	return (new_l);
}
