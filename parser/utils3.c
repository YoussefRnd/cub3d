/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:44:07 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/11/26 18:13:36 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	skip_whitespace(const char *str, t_AtoiIndices *indices)
{
	while (ft_isspace(str[indices->i]))
		indices->i++;
}

bool	check_length(const char *str, t_AtoiIndices *indices)
{
	return (ft_strlen(&str[indices->i]) <= 3);
}

void	handle_sign(const char *str, t_AtoiIndices *indices)
{
	if (str[indices->i] == '-' || str[indices->i] == '+')
	{
		if (str[indices->i] == '-')
			indices->sign = -1;
		indices->i++;
	}
}

int	get_y(t_mapp *head)
{
	int	height;

	height = 0;
	while (head)
	{
		height++;
		head = head->next;
	}
	return (height);
}
