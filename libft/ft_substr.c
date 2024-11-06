/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:06:47 by tsaari            #+#    #+#             */
/*   Updated: 2024/11/06 15:06:17 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*sc;
	char *empty_str = ft_strdup("");
    

	sc = (char *)s;
	if (!s)
		return (0);
	if (len + (size_t)start >= ft_strlen(sc))
		len = ft_strlen(sc) - start;
	if ((size_t)start >= ft_strlen(sc))
	{
		empty_str = ft_strdup("");
		if (!empty_str)
        	return NULL;
		return (empty_str);
	}
		return (empty_str);
	ret = (char *)malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (0);
	sc += start;
	len += 1;
	ft_strlcpy(ret, sc, len);
	return (ret);
}
