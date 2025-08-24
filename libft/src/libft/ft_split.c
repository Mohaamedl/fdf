/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:51:07 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 09:34:00 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(const char *s, char c)
{
	int		count;
	int		in_word;

	if (!s)
		return (0);
	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_word_dup(const char *src, int len)
{
	char	*word;
	int		i;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = src[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static int	ft_free_split(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

static int	ft_fill_words(char **result, const char *s, char c)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = 0;
			while (s[start] && s[start] != c)
				start++;
			len = start;
			result[i] = ft_word_dup(s, len);
			if (!result[i])
			{
				return (ft_free_split(result, i));
			}
			s += len;
			i++;
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_wcount(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	result[word_count] = NULL;
	if (!ft_fill_words(result, s, c))
		return (NULL);
	return (result);
}
