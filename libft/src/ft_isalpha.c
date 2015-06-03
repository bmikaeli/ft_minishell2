/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <bmikaeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:55:54 by bmikaeli          #+#    #+#             */
/*   Updated: 2013/11/20 16:09:24 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_isalpha(int c)
{
	if (c > 122)
		return (0);
	else if (c < 97 && c > 90)
		return (0);
	else if (c < 65)
		return (0);
	else
		return (1);
}