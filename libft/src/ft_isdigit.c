/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <bmikaeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:10:32 by bmikaeli          #+#    #+#             */
/*   Updated: 2013/11/20 16:16:45 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_isdigit(int c)
{
	if (c > 57 || c < 48)
		return (0);
	return (1);
}