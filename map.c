/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:44:41 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:19:43 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file includes all the map-related functions.
*/

#include "fillit.h"

/*
** Takes the number of tetriminos.
** Calculates and returns the smallest potential size for the square of the map.
*/

short	get_first_size(short nb)
{
	short	result;
	short	nb_cmp;

	nb *= 4; // to get the total number of #
	result = (nb + 1) / 2 + 1;  // if nb = 8 result = 5.5 so 5
	while (--result) // smallest square possible with 1 square pattern
	{
		nb_cmp = result * result;
		if (nb_cmp == nb)   // if we had nb = 16 we want to return 4 not 5
			return (result);
		if (nb_cmp < nb) // true for result = 3 
			return (result + 1);
	}
	return (0);
}

/*
** Allocated memory to the double int array within the t_map structure and
** sets each int value to 0 (ft_memalloc does that).
** Also initialized other members of the structure: m->size to the size
** passed as parameter, m->i to 0, as we will start iterating through each
** piece starting from the first one, and m->total to num, or, the total
** number of tetriminos we have to place.
*/

short	gen_map(t_map *m, short size, short num)
{
	short	i;

	//printf("generating new map size: %d\n", size);
	if (!(m->m = (short **)ft_memalloc(sizeof(short *) * size)))
		return (0);
	i = 0;
	while (i < size)
	{
		if (!(m->m[i] = (short *)ft_memalloc(sizeof(short) * size)))
			return (0);
		//printf("inside memalloc\n");
		//printf("size: %d\nm->i: %d\nnum: %d\n", size, m->i, num);
		i++;
	}
	m->size = size;
	m->i = 0;
	m->total = num;
	//printf("gen_map success: m->i: %d\nm->size: %d\nm->total: %d\n\n", m->i, m->size, m->total);
	return (1);
}

/*
** Frees allocated memory within the t_map structure, frees the pointer
** and resets the coordinates of placed tetriminos.
** This function is called on in solve, if fill_map returns 0, ie, when
** the tetriminos cannot be placed in a map of a given size.
*/

void	reset_map(t_map *m, t_tetrimino *ts)
{
	short	i;

	//printf("test in reset1\n");
	i = 0;
	while (i < m->size)
		free(m->m[i++]);
	free(m->m);
	//if (m)
	//	free(m);
	//printf("test in reset1\n");
	//if (m)
//		free(m);
	//m = NULL;
	i = 0;
	//printf("total: %d\n", m->total);
	while (i < m->total)
	{
		//printf("Resetting coords\n");
		reset_t_coords(ts + i);
		++i;
	}
}

/*
** Allocates memory to a double char array and sets its values to the
** corresponding char of the tetrimino, or '.'.
** Returns a double char array.
*/

char	**get_final_map(t_map *m, t_tetrimino *ts)
{
	//printf("getting final map\n");
	char	**result;

	if (!(result = (char **)ft_memalloc(sizeof(char *) * (m->size + 1))))
		return (0);
	//printf("check\n");
	//result[m->size] = NULL;
	m->i = 0;
	//printf("result[m->size]: %s\n", result[m->size]);
	while (m->i < m->size + 1)
	{
		//printf("m->:i = %d\n m->total = %d\n", m->i, m->total);
		if (!(result[m->i] = (char *)ft_memalloc(sizeof(char) * (m->size + 1))))
			return (0);
		//result[m->i][m->size] = '\0'; //is this necessary?
		ft_memset(result[m->i], CHAR_EMPTY, m->size);
		++m->i;
	}
	m->i = 0;
	//printf("get_final_map\n");
	//print_result(result, m);
	while (m->i < m->total)  // FOR JAN: if we put m->i < m->total - 1 we have no seg fault but last tetri is not properly added.
	{
		set_char(result, ts + m->i);
		++m->i;
	}
	m->i = 0;
	while (m->i < m->total)
		free(ts[m->i++].pts);
	free(ts);
	//ft_putstr("-------------Success before print--------------\n");
	//printf("result[m->size]: %s\n", result[m->size]);
	return (result);
}

/*
** Sets each char of a tetrimino to the appropriate upper-case letter.
*/

void	set_char(char **result, t_tetrimino *ts)
{
	short	i;

	i = 0;
	while (i < 4)
	{
		result[ts->y + ts->pts[i].y][ts->x + ts->pts[i].x] = ts->i + 65;
		i++;
	}
}
