/**
 *******************************************************************************
 * @file        debug_cmd.h
 * @author      ABOV R&D Division
 * @brief       debug_cmd file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef	_CMD_H_
#define	_CMD_H_

int		cmd_dump(char *cmd);
int		cmd_edit(char *cmd);
int		cmd_write(char *cmd);
int		cmd_fill(char *cmd);
int		cmd_move(char *cmd);
int		cmd_compare(char *cmd);
int 	cmd_execute(char *cmd);
int		cmd_run(char *cmd);

#endif

