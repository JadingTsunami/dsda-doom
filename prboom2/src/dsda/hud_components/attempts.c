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
//	DSDA Attempts HUD Component
//

#include "dsda/split_tracker.h"

#include "base.h"

#include "attempts.h"

static dsda_text_t component;

static void dsda_UpdateComponentText(char* str, size_t max_size) {
  if (!demorecording)
    return;

  snprintf(
    str,
    max_size,
    "%d/%d",
    dsda_SessionAttempts(),
    dsda_DemoAttempts()
  );
}

void dsda_InitAttemptsHC(int x_offset, int y_offset, int vpt, int* args, int arg_count) {
  dsda_InitTextHC(&component, x_offset, y_offset, vpt);
}

void dsda_UpdateAttemptsHC(void) {
  dsda_UpdateComponentText(component.msg, sizeof(component.msg));
  dsda_RefreshHudText(&component);
}

void dsda_DrawAttemptsHC(void) {
  dsda_DrawBasicText(&component);
}
