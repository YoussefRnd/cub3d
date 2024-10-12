/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:49:04 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/12 18:18:54 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*str_dup(char *s1)
{
	char	*dup;
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*concatenate(char *s1, char *s2)
{
	int		s1len;
	int		s2len;
	char	*new;
	int		i;
	int		j;

	if (!s1)
		return (str_dup(s2));
	if (!s2)
		return (str_dup(s1));
	i = -1;
	j = -1;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	new = malloc((s1len + s2len + 1) * sizeof(char));
	if (!new)
		return (free(s1), s1 = NULL, NULL);
	while (++i < s1len)
		new[i] = s1[i];
	while (++j < s2len)
		new[i + j] = s2[j];
	new[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (new);
}

int	find_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*sub_str(char *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	if (size - start < len)
		len = size - start;
	if (start > size)
		return (str_dup(""));
	subs = (char *)malloc(len + 1);
	if (!subs)
		return (NULL);
	while (i < len)
	{
		subs[i] = s[i + start];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
