/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:35:39 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/09 11:31:44 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd1 = open("f1.txt", O_RDONLY);
    // int fd2 = open("t2.txt", O_RDONLY);
    char *str1;
    char *str2;

    while ((str1 = get_next_line(fd1)))
    {
        printf("str1 = %s", str1);
        free(str1);
    }
    return (0);
}
