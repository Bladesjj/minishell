/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_wild_card_continue_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhamdaou <jhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:36:24 by jhamdaou          #+#    #+#             */
/*   Updated: 2025/05/29 23:09:32 by jhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

int	hndl_str_mth(const char *pat, t_exit_norm *sm)
{
	if (sm->p < sm->p_len && pat[sm->p] == '*')
	{
		sm->star = sm->p;
		sm->match = sm->s;
		(sm->p)++;
		return (1);
	}
	else if (sm->star != -1)
	{
		sm->p = sm->star + 1;
		(sm->match)++;
		sm->s = sm->match;
		return (1);
	}
	return (0);
}

int	wach_exist_card(const char *pat, const char *str)
{
	t_exit_norm	sm;

	sm.s_len = ft_strlen(str);
	sm.p_len = ft_strlen(pat);
	sm.s = 0;
	sm.p = 0;
	sm.star = -1;
	sm.match = -1;
	while (sm.s < sm.s_len)
	{
		if (sm.p < sm.p_len && pat[sm.p] == str[sm.s])
		{
			sm.s++;
			sm.p++;
		}
		else if (!hndl_str_mth(pat, &sm))
			return (0);
	}
	while (sm.p < sm.p_len && pat[sm.p] == '*')
		sm.p++;
	return (sm.p == sm.p_len);
}

void	free_file_wild_relc(t_file_wild_relc *relc)
{
	free(relc->tmpint_free);
	free(relc->tmp_free);
}

void	ft_realloc_filew(t_wild_norm *wild, char *s)
{
	t_file_wild_relc	relc;

	relc.i = 0;
	relc.new_is_space = malloc(sizeof(int) * (wild->size + 1));
	relc.new_q_types = malloc(sizeof(int) * (wild->size + 1));
	relc.new_args = malloc(sizeof(char *) * (wild->size + 2));
	relc.new_args[wild->size] = 0;
	while (relc.i < wild->size)
	{
		relc.new_q_types[relc.i] = wild->q_type[relc.i];
		relc.new_is_space[relc.i] = wild->is_space[relc.i];
		relc.new_args[relc.i] = wild->args[relc.i];
		relc.i++;
	}
	relc.new_args[relc.i] = ft_strdup(s);
	relc.new_args[wild->size + 1] = 0;
	(wild->size)++;
	relc.tmp_free = wild->args;
	wild->args = relc.new_args;
	relc.tmpint_free = wild->is_space;
	wild->is_space = relc.new_is_space;
	free(relc.tmpint_free);
	relc.tmpint_free = wild->q_type;
	wild->q_type = relc.new_q_types;
	return (free_file_wild_relc(&relc));
}

int	it_has_star(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
