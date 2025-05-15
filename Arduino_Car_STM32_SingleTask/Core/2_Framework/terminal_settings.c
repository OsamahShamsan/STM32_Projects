#include "terminal_settings.h"
#include "vt100_terminal.h"

static TerminalSettings pending_settings;
static TerminalSettings active_settings;

void terminal_settings_init(void)
{
    terminal_settings_reset_all();
}

void terminal_settings_reset_all(void)
{
    pending_settings.font_color = 0;
    pending_settings.background_color = 7;
    pending_settings.styles = 0;
}

void terminal_settings_apply(void)
{
    active_settings = pending_settings;
    //reset_attributes();
    //set_background_color(active_settings.background_color);
    //set_color(active_settings.font_color);

   // if (active_settings.styles & STYLE_BOLD)
      //  set_bold();
   // if (active_settings.styles & STYLE_ITALIC)
       // set_attributes();
   // if (active_settings.styles & STYLE_UNDERLINE)
       // vt100_terminal_set_underline();
}

void terminal_settings_discard(void)
{
    pending_settings = active_settings;
}

// Enforce safe rule (can't match font and background)
const char* terminal_settings_set_font_color(uint8_t color)
{
    if (color == pending_settings.background_color)
        return "[Error] Font color cannot match background color.";

    pending_settings.font_color = color;
    return "[Settings] Font color updated (Pending).";
}

const char* terminal_settings_set_background_color(uint8_t color)
{
    if (color == pending_settings.font_color)
        return "[Error] Background color cannot match font color.";

    pending_settings.background_color = color;
    return "[Settings] Background color updated (Pending).";
}

const char* terminal_settings_toggle_style(uint8_t style)
{
    pending_settings.styles ^= style;
    return "[Settings] Style toggled (Pending).";
}

TerminalSettings* terminal_settings_get_pending(void)
{
    return &pending_settings;
}

// === Handlers for menu integration ===
const char* terminal_settings_reset_all_action(void)
{
    terminal_settings_reset_all();
    return "[Settings] Reset to defaults.";
}

const char* terminal_settings_save_and_close_action(void)
{
    terminal_settings_apply();
    return "@EXIT@[Settings] Applied and returning to Main Menu.";
}

const char* terminal_settings_discard_action(void)
{
    terminal_settings_discard();
    return "@EXIT@[Settings] Changes discarded. Returning to Main Menu.";
}


