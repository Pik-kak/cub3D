/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:06:47 by tsaari            #+#    #+#             */
/*   Updated: 2024/10/03 11:10:25 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	str_len;

	if (!s)
		return (0);

	str_len = ft_strlen(s);

	// If start is beyond the end of the string, return an empty string
	if ((size_t)start >= str_len)
		return (ft_strdup(""));

	// Adjust len if it exceeds the remaining string length after 'start'
	if (len > str_len - start)
		len = str_len - start;

	// Allocate memory for the substring (+1 for the null terminator)
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (0);

	// Copy the substring and null-terminate it
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
