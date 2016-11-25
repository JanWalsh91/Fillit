/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:28:33 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 15:04:33 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains the major functions for solving fillit.
*/

#include "fillit.h"

/*
** Attempts to fill maps with the tetriminos, incremeting its size until
** successful.
** Returns the map structure.
*/

t_map	solve(t_tetrimino *ts, short size, short num)
{
	t_map	map;

	gen_map(&map, size, num);
	if (!fill_map(&map, ts))
	{
		reset_map(&map, ts);
		map = solve(ts, size + 1, num);
	}
	return (map);
}

/*
** Attempts to place each piece by placing and removing them until all
** have been placed.
** Returns 1 if all pieces have been placed.
** Returns 0 if all the pieces cannot be placed.
*/

short	fill_map(t_map *m, t_tetrimino *ts)
{
	while (m->i >= 0 && m->i < m->total && ts[m->i].x < m->size &&
			ts[m->i].y < m->size)
	{
		if (!(place_t(m, ts + m->i)))
			remove_t(m, ts);
	}
	if (m->i == m->total)
		return (1);
	return (0);
}

/*
** Attempts tp place a single tetrimino on the map.
** Returns 1 if successfful.
** Returns 0 if unseccessful.
*/

short	place_t(t_map *m, t_tetrimino *ts)
{
	while (ts->x < m->size &&
			ts->y < m->size)
	{
		if (update_map(m, ts))
			return (1);
	}
	return (0);
}

/*
** Removes tetrimino number (m->i - 1).
** Increments the coords of tetrimino (m->i - 1).
** Decrements the index of the tetrimino to be placed (m->i).
** Resets coords of tetrimino number (m->i).
*/

void	remove_t(t_map *m, t_tetrimino *ts)
{
	short	i;

	reset_t_coords(ts + m->i);
	i = 0;
	--m->i;
	if (m->i < 0)
		return ;
	while (i < 4)
	{
		m->m[ts[m->i].pts[i].y + ts[m->i].y]
			[ts[m->i].pts[i].x + ts[m->i].x] = 0;
		i++;
	}
	increment_t_coords(ts + m->i, m);
}

/*
** Checks if the four points of a tetrimino can be placed on the map.
** If possible, places them, increments m->i and returns 1.
** If not possible, returns 0.
*/

short	update_map(t_map *m, t_tetrimino *ts)
{
	short	i;

	i = 0;
	while (i < 4)
	{
		if (((ts->pts[i].y + ts->y >= m->size) ||
				(ts->pts[i].x + ts->x >= m->size) ||
				m->m[ts->pts[i].y + ts->y][ts->pts[i].x + ts->x]))
		{
			increment_t_coords(ts, m);
			return (0);
		}
		++i;
	}
	i = 0;
	while (i < 4)
	{
		m->m[ts->pts[i].y + ts->y][ts->pts[i].x + ts->x] = 1;
		++i;
	}
	m->i++;
	return (1);
}
