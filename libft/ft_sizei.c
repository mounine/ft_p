/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizei.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboeuf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 08:24:08 by eboeuf            #+#    #+#             */
/*   Updated: 2015/05/08 08:24:44 by eboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int			ft_sizei(char *s)
{
	int		i;

	i = 0;
	if (s[0] == '-' || s[0] == '+' || s[0] == ' ' || s[0] == '#')
		i++;
	while (ft_isdigit(s[i]) > 0)
		i++;
	return (i);
}
