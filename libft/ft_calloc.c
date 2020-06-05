/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 23:43:28 by ltouret           #+#    #+#             */
/*   Updated: 2019/11/05 13:19:32 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*dst;
	unsigned int	total;
	unsigned int	i;

	total = ((count * size) == 0) ? 1 : count * size;
	if (!(dst = malloc(total)))
		return (NULL);
	i = 0;
	while (total--)
		dst[i++] = 0;
	return ((void *)dst);
}
