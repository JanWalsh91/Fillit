/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:10:33 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:03:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**t_split(char *s, short num)
{
	short	i;
	char	**result;

	if (!s || !(result = (char **)ft_memalloc(sizeof(char *) * (num + 1))))
		return (NULL);
	s = ft_strjoin(s, "\n");
	//result[num] = NULL;
	i = 0;
	while (*s != '\0' && num > 0)
	{
		//printf("t_count: %lu\n", t_count);
		//printf("location in s: \n%s\n", (char *)s);
		//printf("adding: \n%s\n", ft_strsub((char *)s, (T_SIZE + 1) * i, T_SIZE));
		if (!(result[i] = ft_strsub((char *)s, (T_SIZE + 1) * i, T_SIZE + 1)))
			return (NULL);
		num--;
		i++;
	}
	//result[i][T_SIZE - 1] = '\n';
	//result[i][T_SIZE] = '\0';
	//printf("result: \n%s\n", result[3]);
	return (result);
}
