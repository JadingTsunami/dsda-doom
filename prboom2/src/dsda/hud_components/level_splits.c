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
//	DSDA Level Splits HUD Component
//

#include "dsda/split_tracker.h"

#include "base.h"

#include "level_splits.h"

static dsda_text_t time_component;
static dsda_text_t total_component;

extern int leveltime, totalleveltimes;

static int dsda_SplitComparisonDelta(dsda_split_time_t* split_time) {
  return split_time->ref ? split_time->ref_delta : split_time->best_delta;
}

static void dsda_UpdateIntermissionTime(dsda_split_t* split) {
  char* s;
  char delta[16];
  char color;

  delta[0] = '\0';
  color = HUlib_Color(CR_GRAY);

  if (split && !split->first_time) {
    const char* sign;
    int diff;

    diff = dsda_SplitComparisonDelta(&split->leveltime);
    sign = diff >= 0 ? "+" : "-";
    color = diff >= 0 ? HUlib_Color(CR_GRAY) : HUlib_Color(CR_GREEN);
    diff = abs(diff);

    if (diff >= 2100) {
      snprintf(
        delta, sizeof(delta),
        " (%s%d:%05.2f)",
        sign, diff / 35 / 60, (float)(diff % (60 * 35)) / 35
      );
    }
    else {
      snprintf(
        delta, sizeof(delta),
        " (%s%04.2f)",
        sign, (float)(diff % (60 * 35)) / 35
      );
    }
  }

  snprintf(
    time_component.msg,
    sizeof(time_component.msg),
    "\x1b%c%d:%05.2f",
    color, leveltime / 35 / 60,
    (float)(leveltime % (60 * 35)) / 35
  );

  strcat(time_component.msg, delta);

  dsda_RefreshHudText(&time_component);
}

static void dsda_UpdateIntermissionTotal(dsda_split_t* split) {
  char* s;
  char delta[16];
  char color;

  delta[0] = '\0';
  color = HUlib_Color(CR_GRAY);

  if (split && !split->first_time) {
    const char* sign;
    int diff;

    diff = dsda_SplitComparisonDelta(&split->totalleveltimes) / 35;
    sign = diff >= 0 ? "+" : "-";
    color = diff >= 0 ? HUlib_Color(CR_GRAY) : HUlib_Color(CR_GREEN);
    diff = abs(diff);

    if (diff >= 60) {
      snprintf(
        delta, sizeof(delta),
        " (%s%d:%02d)",
        sign, diff / 60, diff % 60
      );
    }
    else {
      snprintf(
        delta, sizeof(delta),
        " (%s%d)",
        sign, diff % 60
      );
    }
  }

  snprintf(
    total_component.msg,
    sizeof(total_component.msg),
    "\x1b%c%d:%02d",
    color, totalleveltimes / 35 / 60,
    (totalleveltimes / 35) % 60
  );

  strcat(total_component.msg, delta);

  dsda_RefreshHudText(&total_component);
}

void dsda_InitLevelSplitsHC(int x_offset, int y_offset, int vpt, int* args, int arg_count) {
  dsda_InitTextHC(&time_component, x_offset, y_offset, vpt);
  dsda_InitTextHC(&total_component, x_offset, y_offset + 8, vpt);
}

void dsda_UpdateLevelSplitsHC(void) {
  // nothing to do
}

void dsda_DrawLevelSplitsHC(void) {
  char* s;
  dsda_split_t* split;

  split = dsda_CurrentSplit();

  dsda_UpdateIntermissionTime(split);
  dsda_UpdateIntermissionTotal(split);

  dsda_DrawBasicText(&time_component);
  dsda_DrawBasicText(&total_component);
}
