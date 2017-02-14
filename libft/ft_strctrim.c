/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:02:01 by cdrouet           #+#    #+#             */
/*   Updated: 2015/11/27 16:34:08 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strctrim(char const *s, char c)
{
	char			*ptr;
	unsigned long	i;
	unsigned long	j;

	ptr = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ptr)
	{
		i = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
		{
			ptr[0] = '\0';
			return (ptr);
		}
		j = ft_strlen(s) - 1;
		while (s[j] == c)
			j--;
		ptr = ft_strsub(s, i, j - i + 1);
		ptr[j - i + 1] = '\0';
	}
	return (ptr);
}
