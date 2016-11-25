/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:28:33 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:08:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Generates map and attempts to fill map, resetting the map and tetrimino coords
** and incrementing size until succesfful.
** Returns the map.
*/

// MODIFY TYPE SIZE TO t_size
// SIMPLIFY T STRUCTURE (placement coordinates)

t_map	solve(t_tetrimino *ts, short size, short num)
{
	t_map	map;
	//t_map	*m;

	//m = &map;
	//printf("size: %i\nnum: %d\n", size, num);
	//if (!(gen_map(m, size, num)))
	//	return (NULL);
	gen_map(&map, size, num);
	//printf("m->total : %d\n", m->total);
	//printf("in solve: m->i: %d\n", m->i);
	//printf("in solve: m->total: %d\n", m->total);
	//printf("in solve: m->size: %d\n", m->size);
	//printf("check\n");
	if (!fill_map(&map, ts))
	{
		//printf("Filling map Failed\n");
		reset_map(&map, ts);
		//ft_putstr("Reset Successful\n");
		map = solve(ts, size + 1, num);
	}
	return (map);
}

/*
** Attempts to place each piece by placing and removing them until all
** have been placed.
** Returns 1 if all pieces have been placed.
** Returns 0 if pieces cannot all be placed (map size too small).
*/

short	fill_map(t_map *m, t_tetrimino *ts)
{
	//ft_putnbr(m->i);
	//ft_putstr("----------------------------------------------\nBegin fill_map\n");
	while (m->i >= 0 && m->i < m->total && ts[m->i].x < m->size &&
			ts[m->i].y < m->size)
	{
		if (!(place_t(m, ts + m->i))) // Need to pass a single tetrimino by address.
			remove_t(m, ts); // Remove tetrimino number (m->i - 1)
	} 
	if (m->i == m->total) // if we have passed the amount of ts to be placed, then
		return (1);
	else // in case m->i < 0
		return (0);
}

/*
 ** Attempts tp place a single tetrimino on the map.
 ** Returns 1 if successfful
 ** Returns 0 if unseccessful
 */

short	place_t(t_map *m, t_tetrimino *ts)
{
	//printf("CHECK\n");
	//printf("m->i: %d\n", m->i);
	//printf("ts->p.x: %d\n", ts->p.x);
	//printf("ts->p.y: %d\n", ts->p.y);
	//printf("-- place_t: placing T#%d at (%d, %d)\n", m->i, ts->p.x, ts->p.y);
	while (ts->x < m->size &&
			ts->y < m->size)
	// While coordinates are still valid (update_t_coords sets the coords to 
	// size after (size-1, size-1)) tries to update_map until succesfful.
	// update_map will call on update_t_coords if unsuccessful. 
	// update_map will increment m->i if successful.
	{
		//printf("m->i value : %d\n", m->i);
		if (update_map(m, ts))
			return (1);
		//printf("check2\n");
	}
	// Function reaches this point when the update_map was unsuccessful for
	// all points on the map (ie, the pieces doesn't fit anywhere on the map).
	//printf("Place_t fail\n");
	return (0);
}

/*
** Remove tetrimino number (m->i - 1)
** Resets coords of tetrimino number (m->i)
** Increments the coords of tetrimino (m->i-1)
** Decrements the index of the t to be placed (ie : --m->i)
*/

void	remove_t(t_map *m, t_tetrimino *ts)
{
	short	 i;
	//printf("-- remove_t #%d\n", m->i - 1);

	reset_t_coords(ts + m->i); //Reset coordinates of the current tetrimino,
	//since we will try to place it wherever possible after the previous one
	//has been replaced.
	i = 0;
	--m->i; //decrement next tetrimino to place. We are now working with the previous tetrimino:
	if (m->i < 0)
		return ;
	while (i < 4) // For each point, reset it to 0 on the map.
	{
		m->m[ts[m->i].pts[i].y + ts[m->i].y][ts[m->i].pts[i].x + ts[m->i].x] = 0;
		i++;
	}
	increment_t_coords(ts + m->i, m);
}

/*
** Tries to place the four points on the map.
** Returns 1 if successful, 0 if unsuccessful.
** First checks the validity of coordinates and value of the point.
** If any one of them are invalid, it will increment the coords and return (0);
** If they are all valid, reiterate through and set the 4 points to 1;
** Finally, iterate m->i, to try to place the next piece.
*/

short	update_map(t_map *m, t_tetrimino *ts)
{
	short	i;

	i = 0;
	while (i < 4)
	{
		//printf("Checking if point is valid: T#%d pt#%d\n", m->i, i);
		if (((ts->pts[i].y + ts->y >= m->size) ||
				(ts->pts[i].x + ts->x >= m->size) ||
				m->m[ts->pts[i].y + ts->y][ts->pts[i].x + ts->x]))
		{
			//printf("T#%d pt#%d: (%d, %d) -> ", m->i, i, (ts)->p.x, (ts)->p.y);
			increment_t_coords(ts, m);
			//printf("(%d, %d)\n", (ts)->p.x, (ts)->p.y);
			return (0);
		}
		++i;
	}
	i = 0;
	while (i < 4)
	{
		m->m[ts->pts[i].y + ts->y][ts->pts[i].x + ts->x] = 1;
		//printf("Placed point %d at (%d, %d)\n", i, ts->pts[i].x + ts->p.x, ts->pts[i].y + ts->p.y);
		++i;
	}
	//printf("T#%d placed at (%d, %d)\n", m->i, ts->p.x, ts->p.y);
	//printf("\n\n");
	//print_t_map(*m);
	//ft_putstr("\n");
	m->i++;
	return (1);
}
