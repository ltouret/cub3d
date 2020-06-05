/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:32:30 by ltouret           #+#    #+#             */
/*   Updated: 2019/10/22 18:30:13 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list *ret;

	if ((ret = (t_list*)(malloc(sizeof(t_list)))))
	{
		ret->content = content;
		ret->next = NULL;
	}
	return (ret);
}
