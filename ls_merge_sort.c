/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:05:51 by mrandou           #+#    #+#             */
/*   Updated: 2018/04/25 15:13:36 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	pos_list(t_list *list, t_list **lst1, t_list **lst2)
{
	t_list	*fast;
	t_list	*slow;

	slow = list;
	fast = list->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*lst1 = list;
	*lst2 = slow->next;
	slow->next = NULL;
}

t_list	*disp_list(t_list *lst1, t_list *lst2, int (*f_cmp)(t_list *, t_list *))
{
	t_list	*rslt;

	rslt = NULL;
	if (!lst1)
		return (lst2);
	else if (!lst2)
		return (lst1);
	if (f_cmp(lst1->content, lst2->content) > 0)
	{
		rslt = lst2;
		rslt->next = disp_list(lst1, lst2->next, f_cmp);
	}
	else
	{
		rslt = lst1;
		rslt->next = disp_list(lst1->next, lst2, f_cmp);
	}
	return (rslt);
}

void	ls_merge_sort(t_list **list, int (*f_cmp)(t_list *, t_list *))
{
	t_list	*head;
	t_list	*lst1;
	t_list	*lst2;

	head = *list;
	lst1 = NULL;
	lst2 = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	pos_list(head, &lst1, &lst2);
	ls_merge_sort(&lst1, f_cmp);
	ls_merge_sort(&lst2, f_cmp);
	*list = disp_list(lst1, lst2, f_cmp);
}
