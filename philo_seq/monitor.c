/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:48 by kwang             #+#    #+#             */
/*   Updated: 2021/12/02 15:05:49 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_args *args, t_philo *philo, unsigned long curr_time)
{
	long unsigned	death_time;

	death_time = philo->last_eat_time + args->conds.tt_die;
	if (curr_time >= death_time)
		args->death = 1;
	return (args->death);
}

void	death_monitor(t_args *args)
{
	int				i;
	unsigned long	curr_time;
	int				max_eat;

	args->start = 1;
	milisleep(args->conds.tt_die);
	max_eat = args->conds.max_eat_num;
	while (!args->death && !(max_eat > 0
			&& args->all_full >= args->conds.philo_num))
	{
		i = -1;
		while (++i < args->conds.philo_num)
		{
			curr_time = get_time();
			if (!(max_eat > 0 && args->all_full >= args->conds.philo_num)
				&& check_death(args, &args->philos[i], curr_time))
			{
				pthread_mutex_lock(args->print_mutex);
				printf("%lu %d %s\n", curr_time, i + 1, "died");
				pthread_mutex_unlock(args->print_mutex);
				break ;
			}
		}
	}
}
