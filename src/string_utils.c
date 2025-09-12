/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/12 14:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	count_words(const char *str, char delimiter)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != delimiter && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (str[i] == delimiter)
			in_word = 0;
		i++;
	}
	return (count);
}

char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r'))
		str++;
	return (str);
}

static int	parse_sign_and_get_start(const char *str, int *sign)
{
	int	i;

	*sign = 1;
	i = 0;
	if (str[0] == '-')
	{
		*sign = -1;
		i = 1;
	}
	else if (str[0] == '+')
		i = 1;
	return (i);
}

int	string_to_int_len(const char *str, int len)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	i = parse_sign_and_get_start(str, &sign);
	while (i < len && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
