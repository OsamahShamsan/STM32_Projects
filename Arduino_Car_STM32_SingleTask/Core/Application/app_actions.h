#ifndef APP_ACTIONS_H_
#define APP_ACTIONS_H_

// LED actions
const char* led_toggle_action(void);
const char* led_on_action(void);
const char* led_off_action(void);

// System Info actions
const char* show_board_info(void);
const char* show_firmware_version(void);

// Terminal Settings actions (indirect handlers)
const char* terminal_set_font_color_handler(void);
const char* terminal_set_bg_color_handler(void);
const char* terminal_toggle_bold_action(void);
const char* terminal_toggle_italic_action(void);
const char* terminal_toggle_underline_action(void);

// Quit
const char* quit_handler(void);

#endif // APP_ACTIONS_H_
