/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:43:30 by ltouret           #+#    #+#             */
/*   Updated: 2019/10/25 16:15:46 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**if_err(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	return (arr);
}

int		str_count(char const *s, char c)
{
	int		sta;
	int		end;
	int		count;

	sta = 0;
	end = ft_strlen(s);
	count = 0;
	while (s[sta] == c && s[sta])
		sta++;
	while (s[end] == c && s[end])
		end--;
	while (end > sta)
	{
		while (s[sta] != c && end > sta)
			sta++;
		while (s[sta] == c && end > sta)
			sta++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		sta;
	int		i;
	int		o;

	o = 0;
	i = -1;
	if (!s)
		return (NULL);
	if ((arr = (char**)(malloc(sizeof(char*) * (str_count(s, c) + 1)))))
	{
		while (str_count(s, c) > ++i)
		{
			while (s[o] == c && s[o])
				o++;
			sta = o;
			while (s[o] != c && s[o])
				o++;
			if (!(arr[i] = (char*)(malloc(sizeof(*arr[i]) * ((o - sta) + 1)))))
				return (if_err(arr));
			ft_strlcpy(arr[i], s + sta, (o - sta) + 1);
		}
		arr[i] = 0;
	}
	return (arr);
}
