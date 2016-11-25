/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:20:24 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/24 14:29:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Takes a pointer to a t_tetrimino and sets the coordinates where it needs
** to be placed to 0. 
*/

void	reset_t_coords(t_tetrimino *ts)
{
	//printf("reset_t_coords\n");
	ts->x = 0;
	ts->y = 0;
}

/*
** Increments the coordinates of a tetrimino to be placed.
** If they indicate the last point (bottom right) on the map,
** sets them to size (to indicate in other functions that this
** tetrimino cannot be placed on the map given current tetrimino
** configuartion and map size.
** Increments x. If x=size (outside the map), increments y and resets
** x to 0.
*/

void	increment_t_coords(t_tetrimino *ts, t_map *m)
{
	if (ts->x == m->size - 1 &&
			ts->y == m->size - 1)
	{
		ts->x = m->size;
		ts->y = m->size;
		return ;
	}
	++ts->x;
	if (ts->x == m->size)
	{
		ts->x = 0;
		++ts->y;
	}
}
