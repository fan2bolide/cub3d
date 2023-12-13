/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_mouse_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:50:31 by bajeanno          #+#    #+#             */
/*   Updated: 2023/12/13 00:50:39 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int cub_handle_mouse_release(int button, int x, int y, t_cub *cub)
{
	(void)button;
	(void)x;
	(void)y;
	if (cub->menu.cursors[SPEED].is_pressed)
		cub->menu.cursors[SPEED].is_pressed = false;
	if (cub->menu.cursors[SENSI].is_pressed)
		cub->menu.cursors[SENSI].is_pressed = false;
	if (cub->menu.reseters[SPEED].is_pressed)
		cub->menu.reseters[SPEED].is_pressed = false;
	if (cub->menu.reseters[SENSI].is_pressed)
		cub->menu.reseters[SENSI].is_pressed = false;
	return (0);
}

int	cub_handle_mouse(int button, int x, int y, t_cub *cub)
{
	(void)button;
	if (!cub->menu.on_screen)
		return (1);
	if (x >= cub->menu.x + 516 && x < cub->menu.x + 516 + cub->menu.checker_plain.width && y >= cub->menu.y + 578 && y < cub->menu.y + 578 + cub->menu.checker_plain.height)
		cub->menu.outline = 2;
	if (x >= cub->menu.x + 516 && x < cub->menu.x + 516 + cub->menu.checker_plain.width && y >= cub->menu.y + 507 && y < cub->menu.y + 507 + cub->menu.checker_plain.height)
		cub->menu.outline = 1;
	if (x >= cub->menu.x + 382 && x < cub->menu.x + 382 + cub->menu.checker_plain.width && y >= cub->menu.y + 322 && y < cub->menu.y + 322 + cub->menu.checker_plain.height)
		cub->menu.cross_hair = 1;
	if (x >= cub->menu.x + 477 && x < cub->menu.x + 477 + cub->menu.checker_plain.width && y >= cub->menu.y + 322 && y < cub->menu.y + 322 + cub->menu.checker_plain.height)
		cub->menu.cross_hair = 2;
	if (x >= cub->menu.x + 420 && x < cub->menu.x + 420 + cub->menu.button.width && y >= cub->menu.y + 60 && y < cub->menu.y + 60 + cub->menu.button.height)
		handle_menu(cub);
	if ((x - cub->menu.x >= cub->menu.cursors[SPEED].x && x - cub->menu.x < cub->menu.cursors[SPEED].x + cub->menu.cursor.width && y - abs(cub->menu.y) >= cub->menu.cursors[SPEED].y && y - abs(cub->menu.y) < cub->menu.cursors[SPEED].y + cub->menu.cursor.height) || (x - cub->menu.x >= 870 && x - cub->menu.x < 1300 && y - cub->menu.y >= 350 && y - cub->menu.y < 390))
	{
		cub->menu.cursors[SPEED].is_pressed = true;
		cub->menu.cursors[SPEED].press_x = x;
		cub->menu.cursors[SPEED].press_y = y;
	}
	if ((x - cub->menu.x >= cub->menu.cursors[SENSI].x && x - cub->menu.x < cub->menu.cursors[SENSI].x + cub->menu.cursor.width && y - abs(cub->menu.y) >= cub->menu.cursors[SENSI].y && y - abs(cub->menu.y) < cub->menu.cursors[SENSI].y + cub->menu.cursor.height) || (x - cub->menu.x >= 870 && x - cub->menu.x < 1300 && y - cub->menu.y >= 548 && y - cub->menu.y < 588))
	{
		cub->menu.cursors[SENSI].is_pressed = true;
		cub->menu.cursors[SENSI].press_x = x;
		cub->menu.cursors[SENSI].press_y = y;
	}
	if ((x - cub->menu.x >= cub->menu.reseters[SPEED].x && x - cub->menu.x < cub->menu.reseters[SPEED].x + cub->menu.reset.width && y - abs(cub->menu.y) >= cub->menu.reseters[SPEED].y && y - abs(cub->menu.y) < cub->menu.reseters[SPEED].y + cub->menu.reset.height))// || (x - cub->menu.x >= 870 && x - cub->menu.x < 1300 && y - cub->menu.y >= 548 && y - cub->menu.y < 588))
	{
		cub->menu.reseters[SPEED].is_pressed = true;
		cub->menu.reseters[SPEED].press_x = x;
		cub->menu.reseters[SPEED].press_y = y;
	}
	if ((x - cub->menu.x >= cub->menu.reseters[SENSI].x && x - cub->menu.x < cub->menu.reseters[SENSI].x + cub->menu.reset.width && y - abs(cub->menu.y) >= cub->menu.reseters[SENSI].y && y - abs(cub->menu.y) < cub->menu.reseters[SENSI].y + cub->menu.reset.height)) //|| (x - cub->menu.x >= 870 && x - cub->menu.x < 1300 && y - cub->menu.y >= 548 && y - cub->menu.y < 588))
	{
		cub->menu.reseters[SENSI].is_pressed = true;
		cub->menu.reseters[SENSI].press_x = x;
		cub->menu.reseters[SENSI].press_y = y;
	}
	return (0);
}
