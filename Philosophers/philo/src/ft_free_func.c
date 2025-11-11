/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:13 by xalves            #+#    #+#             */
/*   Updated: 2025/07/04 10:24:48 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/// @brief Frees the entire stacks/node
/// @param stack Stack to be Freed
void	ft_free_stack(t_list *stack)
{
	t_list	*tmp;

	while (stack)
	{
		tmp = stack->next;
		if (stack->binary)
			free(stack->binary);
		free(stack);
		stack = tmp;
	}
}

/// @brief Frees the entire stacks/node && aux_arr before saying error
/// @param a_stk Stack to be Freed
/// @param aux_arr array to be Freed
/// @return returns an Error mesage
int	free_before_leave(t_list *a_stk, int *aux_arr)
{
	ft_free_stack(a_stk);
	free(aux_arr);
	return (ft_putstr_fd("Error\n", 2), 1);
}

/// @brief Frees everything
/// @param a_stack stack a
/// @param b_stack stack b
/// @param aux_array array where i sorted the contents
void	free_all(t_list *a_stack, t_list *b_stack, int *aux_array)
{
	free(aux_array);
	ft_free_stack(a_stack);
	ft_free_stack(b_stack);
}
