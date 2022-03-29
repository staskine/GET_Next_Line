/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staskine <staskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:43:55 by staskine          #+#    #+#             */
/*   Updated: 2022/03/03 12:20:10 by staskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"

# define BUFF_SIZE 8
# define FD_SIZE 4096

int	get_next_line(const int fd, char **line);

#endif
