//
// Copyright(C) 2022 by Ryan Krafnick
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	DSDA Armor Text HUD Component
//

#ifndef __DSDA_HUD_COMPONENT_ARMOR_TEXT__
#define __DSDA_HUD_COMPONENT_ARMOR_TEXT__

void dsda_InitArmorTextHC(int x_offset, int y_offset, int vpt_flags, int* args, int arg_count);
void dsda_UpdateArmorTextHC(void);
void dsda_DrawArmorTextHC(void);

#endif
