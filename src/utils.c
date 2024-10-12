/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:31:55 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/10/12 18:10:30 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	free_and_set_to_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*trim_white_spaces(char *str)
{
	char	*trimmed_str;

	int start, end, i;
	if (str == NULL)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'))
		end--;
	trimmed_str = malloc(end - start + 2);
	if (trimmed_str == NULL)
		return (NULL);
	i = start;
	while (i <= end)
	{
		trimmed_str[i - start] = str[i];
		i++;
	}
	trimmed_str[i - start] = '\0';
	return (trimmed_str);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

int	ft_super_atoi(const char *str)
{
	int i = 0;
	int num = 0;
	int sign = 1;

	while (ft_isspace((unsigned char)str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit((unsigned char)str[i]))
		return (-1);
	while (ft_isdigit((unsigned char)str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	num *= sign;
	if (num < 0 || num > 255)
		return (-1);
	return (num);
}
