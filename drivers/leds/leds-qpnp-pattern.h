#ifndef __LEDS_QPNP_PATTERN_H_INCLUDED
#define __LEDS_QPNP_PATTERN_H_INCLUDED

#include <led-pattern.h>
#include <linux/qpnp/pwm.h>

/*  Pattern data structure
 *
 *  0 ............. 23                  [LUT TABLE]
 *
 *  START       LENGTH
 *  24          25                      [RED]
 *  26          27                      [GRN]
 *  28          29                      [BLU]
 *
 *  PAUSE_LO    PAUSE_HI    PAUSE_STEP  [R/G/B COMMON]
 *  30          31          32
 *  FLAGS
 *  33
 */

// Sizes of a pattern data structure
#define PATTERN_SIZE_ARRAY          34
#define PATTERN_SIZE_LUT            24

// Time parameters in MilliSec.
#define PATTERN_STEP_DEFAULT        100
#define PATTERN_STEP_CHARGING       100
#define PATTERN_STEP_POWERONOFF     50
#define PATTERN_STEP_NOTI           50
#define PATTERN_PAUSE_DISABLED      0
#define PATTERN_PAUSE_HI_CHARGING   1000
#define PATTERN_PAUSE_HI_NOTI       (12000 - (PATTERN_STEP_NOTI*7))
#define PATTERN_PAUSE_HI_URGENT     (12000 - (PATTERN_STEP_NOTI*11))

// Pattern flags for the LPG
#define PATTERN_FLAG_ONESHOT        /*0x42*/ (PM_PWM_LUT_USE_RAW_VALUE|PM_PWM_LUT_RAMP_UP)
#define PATTERN_FLAG_SOLID          /*0x43*/ (PATTERN_FLAG_ONESHOT|PM_PWM_LUT_LOOP)
#define PATTERN_FLAG_REPEAT         /*0x4B*/ (PATTERN_FLAG_ONESHOT|PM_PWM_LUT_PAUSE_HI_EN|PM_PWM_LUT_LOOP)
#define PATTERN_FLAG_WAVEFORM       /*0x4F*/ (PATTERN_FLAG_REPEAT|PM_PWM_LUT_REVERSE)
#define PATTERN_FLAG_BLINK          /*0x5B*/ (PATTERN_FLAG_REPEAT|PM_PWM_LUT_PAUSE_LO_EN)

// Index in a pattern data structure
#define PATTERN_INDEX_RED_START     24
#define PATTERN_INDEX_RED_LENGTH    25
#define PATTERN_INDEX_GREEN_START   26
#define PATTERN_INDEX_GREEN_LENGTH  27
#define PATTERN_INDEX_BLUE_START    28
#define PATTERN_INDEX_BLUE_LENGTH   29
#define PATTERN_INDEX_PAUSE_LO      30
#define PATTERN_INDEX_PAUSE_HI      31
#define PATTERN_INDEX_PAUSE_STEP    32
#define PATTERN_INDEX_FLAGS         33


// PATTERN_SCENARIO_DEFAULT_OFF (#0)
static int qpnp_pattern_default_off [] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	 0, 0,
	 8, 0,
	16, 0,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_DEFAULT,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_POWER_ON (#1)
static int qpnp_pattern_power_on [] = {
	  1,   4,   9,  17,  26,  37,  50,  64,  79,  94, 111, 128,
	144, 161, 176, 191, 205, 218, 229, 238, 246, 251, 254, 255,

	0,  0,
	0, 24,  // GREEN and BLUE share 24 entries
	0, 24,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_POWERONOFF,
	PATTERN_FLAG_WAVEFORM
};

// PATTERN_SCENARIO_POWER_OFF (#6)
static int qpnp_pattern_power_off [] = {
	  1,   4,   9,  17,  26,  37,  50,  64,  79,  94, 111, 128,
	144, 161, 176, 191, 205, 218, 229, 238, 246, 251, 254, 255,

	0,  0,
	0, 24,  // GREEN and BLUE share 24 entries
	0, 24,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_POWERONOFF,
	PATTERN_FLAG_WAVEFORM
};

// PATTERN_SCENARIO_LCD_ON (#2)
static int qpnp_pattern_lcd_on[] = {
	/* GREEN/BLUE : 8 */
	  0,   0,   0,   0,   0,   0,  0, 0,
	255, 255, 255, 255, 255, 173, 58, 0,
	255, 255, 255, 255, 255, 173, 58, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_DEFAULT,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_CHARGING (#3)
static int qpnp_pattern_charging[] = {
	/* RED : 24 */
	13, 14, 16, 19, 21, 25, 30, 35, 40,  45,  51,  57,
	63, 68, 74, 79, 84, 88, 92, 96, 98, 100, 101, 102,

	0, 24,
	0,  0,
	0,  0,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_CHARGING, PATTERN_STEP_CHARGING,
	PATTERN_FLAG_WAVEFORM
};

// PATTERN_SCENARIO_CHARGING_FULL (#4)
static int qpnp_pattern_charging_full [] = {
	/* GREEN : 2 */
	76, 76,
	/* DUMMY : 22 */
	 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	0, 0,
	0, 2,
	0, 0,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_DEFAULT,
	PATTERN_FLAG_WAVEFORM
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_FAVORITE (#36)
static int qpnp_pattern_missed_noti_favorite [] = {
	/* This pattern is deprecated. */
	0, 4, 23, 52, 104, 141, 170, 179,
	0, 1,  3,  7,  15,  20,  24,  25,
	0, 5, 33, 74, 148, 201, 242, 255,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_DEFAULT,
	PATTERN_FLAG_WAVEFORM
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_URGENT (#37)
static int qpnp_pattern_missed_noti_urgent [] = {
	/* RED : 12 */
	255, 250, 240, 0, 255, 250, 240, 0, 255, 250, 240, 0,
	  0,   0,   0, 0,   0,   0,   0, 0,   0,   0,   0, 0,

	0, 12,
	0,  0,
	0,  0,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_URGENT, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_GREEN (#7)
static int qpnp_pattern_missed_noti_green [] = {
	/* G : 8 */
	  0,   0, 0, 0, 0,   0,   0, 0,
	255, 250, 0, 0, 0, 255, 250, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_GREEN (#39)
static int qpnp_pattern_missed_noti_green_once [] = {
	/* G : 8 */
	  0,   0, 0, 0, 0,   0,   0, 0,
	255, 250, 0, 0, 0, 255, 250, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_BLUE (#18)
static int qpnp_pattern_missed_noti_blue [] = {
	  0,   0, 0, 0, 0,   0,   0, 0,
	 77,  74, 0, 0, 0,  77,  74, 0,
	255, 250, 0, 0, 0, 255, 250, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_BLUE (#41)
static int qpnp_pattern_missed_noti_blue_once [] = {
	  0,   0, 0, 0, 0,   0,   0, 0,
	 77,  74, 0, 0, 0,  77,  74, 0,
	255, 250, 0, 0, 0, 255, 250, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PINK (#17)
static int qpnp_pattern_missed_noti_pink [] = {
	255, 250, 0, 0, 0, 255, 250, 0,
	 65,  63, 0, 0, 0,  65,  63, 0,
	 65,  63, 0, 0, 0,  65,  63, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PINK (#40)
static int qpnp_pattern_missed_noti_pink_once [] = {
	255, 250, 0, 0, 0, 255, 250, 0,
	 65,  63, 0, 0, 0,  65,  63, 0,
	 65,  63, 0, 0, 0,  65,  63, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_YELLOW (#20)
static int qpnp_pattern_missed_noti_yellow [] = {
	255, 250, 0, 0, 0, 255, 250, 0,
	230, 226, 0, 0, 0, 230, 226, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_YELLOW (#43)
static int qpnp_pattern_missed_noti_yellow_once [] = {
	255, 250, 0, 0, 0, 255, 250, 0,
	230, 226, 0, 0, 0, 230, 226, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_ORANGE (#19)
static int qpnp_pattern_missed_noti_orange [] = {
	255, 250, 0, 0, 0, 255, 250, 0,
	102,  99, 0, 0, 0, 102,  99, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_ORANGE (#42)
static int qpnp_pattern_missed_noti_orange_once [] = {
	255, 250, 0, 0, 0, 255, 250, 0,
	102,  99, 0, 0, 0, 102,  99, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_TURQUOISE (#29)
static int qpnp_pattern_missed_noti_turquoise [] = {
	  0,   0, 0, 0, 0,   0,   0, 0,
	255, 250, 0, 0, 0, 255, 250, 0,
	122, 119, 0, 0, 0, 122, 119, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_TURQUOISE (#44)
static int qpnp_pattern_missed_noti_turquoise_once [] = {
	  0,   0, 0, 0, 0,   0,   0, 0,
	255, 250, 0, 0, 0, 255, 250, 0,
	122, 119, 0, 0, 0, 122, 119, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PURPLE (#30)
static int qpnp_pattern_missed_noti_purple [] = {
	179, 177, 0, 0, 0, 179, 177, 0,
	 25,  25, 0, 0, 0,  25,  25, 0,
	255, 250, 0, 0, 0, 255, 250, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PURPLE (#45)
static int qpnp_pattern_missed_noti_purple_once [] = {
	179, 177, 0, 0, 0, 179, 177, 0,
	 25,  25, 0, 0, 0,  25,  25, 0,
	255, 250, 0, 0, 0, 255, 250, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_RED (#31)
static int qpnp_pattern_missed_noti_red [] = {
	255, 250, 0, 0, 0, 255, 250, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_RED (#46)
static int qpnp_pattern_missed_noti_red_once [] = {
	255, 250, 0, 0, 0, 255, 250, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};

// PATTERN_SCENARIO_MISSED_NOTI_REPEAT_LIME (#32)
static int qpnp_pattern_missed_noti_lime [] = {
	135, 131, 0, 0, 0, 135, 131, 0,
	255, 250, 0, 0, 0, 255, 250, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_HI_NOTI, PATTERN_STEP_NOTI,
	PATTERN_FLAG_REPEAT
};

// PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_LIME (#47)
static int qpnp_pattern_missed_noti_lime_once [] = {
	135, 131, 0, 0, 0, 135, 131, 0,
	255, 250, 0, 0, 0, 255, 250, 0,
	  0,   0, 0, 0, 0,   0,   0, 0,

	 0, 8,
	 8, 8,
	16, 8,

	PATTERN_PAUSE_DISABLED, PATTERN_PAUSE_DISABLED, PATTERN_STEP_NOTI,
	PATTERN_FLAG_ONESHOT
};


/* In the hidden-menu,
 * the pattern numbers 0~15 of seek-bar are mapped to ...
 *
 *  	PATTERN_SCENARIO_DEFAULT_OFF                    = 0,
 *  	PATTERN_SCENARIO_POWER_ON                       = 1,
 *  	PATTERN_SCENARIO_LCD_ON                         = 2,
 *  	PATTERN_SCENARIO_CHARGING                       = 3,
 *  	PATTERN_SCENARIO_CHARGING_FULL                  = 4,
 *  	*PATTERN_SCENARIO_BLANK_5                       = 5,
 *  	PATTERN_SCENARIO_POWER_OFF                      = 6,
 *  	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_GREEN       = 7,
 *  	*PATTERN_SCENARIO_BLANK_8                       = 8,
 *  	*PATTERN_SCENARIO_BLANK_9                       = 9,
 *  	*PATTERN_SCENARIO_BLANK_10                      = 10,
 *  	*PATTERN_SCENARIO_BLANK_11                      = 11,
 *  	*PATTERN_SCENARIO_BLANK_12                      = 12,
 *  	*PATTERN_SCENARIO_BLANK_13                      = 13,
 *  	*PATTERN_SCENARIO_BLANK_14                      = 14,
 *  	*PATTERN_SCENARIO_BLANK_15                      = 15
 */
enum qpnp_pattern_scenario {
	PATTERN_SCENARIO_DEFAULT_OFF                    = 0,

	PATTERN_SCENARIO_POWER_ON                       = 1,
	PATTERN_SCENARIO_POWER_OFF                      = 6,
	PATTERN_SCENARIO_LCD_ON                         = 2,

	PATTERN_SCENARIO_CHARGING                       = 3,
	PATTERN_SCENARIO_CHARGING_FULL                  = 4,

	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_FAVORITE    = 36,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_URGENT      = 37,

	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_GREEN       = 7,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_BLUE        = 18,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PINK        = 17,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_YELLOW      = 20,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_ORANGE      = 19,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_TURQUOISE   = 29,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PURPLE      = 30,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_RED         = 31,
	PATTERN_SCENARIO_MISSED_NOTI_REPEAT_LIME        = 32,

	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_GREEN      = 39,
	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_BLUE       = 41,
	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PINK       = 40,
	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_YELLOW     = 43,
	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_ORANGE     = 42,
	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_TURQUOISE  = 44,
	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PURPLE     = 45,
	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_RED        = 46,
	PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_LIME       = 47,

	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_5            = 5,
	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_8            = 8,
	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_9            = 9,
	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_10           = 10,
	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_11           = 11,
	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_12           = 12,
	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_13           = 13,
	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_14           = 14,
	PATTERN_SCENARIO_HIDDEN_MENU_BLANK_15           = 15,
};

static int* qpnp_pattern_parameter [] = {
	qpnp_pattern_default_off,                //  0 <- PATTERN_SCENARIO_DEFAULT_OFF
	qpnp_pattern_power_on,                   //  1 <- PATTERN_SCENARIO_POWER_ON
	qpnp_pattern_power_off,                  //  2 <- PATTERN_SCENARIO_POWER_OFF
	qpnp_pattern_lcd_on,                     //  3 <- PATTERN_SCENARIO_LCD_ON
	qpnp_pattern_charging,                   //  4 <- PATTERN_SCENARIO_CHARGING
	qpnp_pattern_charging_full,              //  5 <- PATTERN_SCENARIO_CHARGING_FULL
	qpnp_pattern_missed_noti_favorite,       //  6 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_FAVORITE
	qpnp_pattern_missed_noti_urgent,         //  7 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_URGENT
	qpnp_pattern_missed_noti_green,          //  8 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_GREEN
	qpnp_pattern_missed_noti_blue,           //  9 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_BLUE
	qpnp_pattern_missed_noti_pink,           // 10 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PINK
	qpnp_pattern_missed_noti_yellow,         // 11 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_YELLOW
	qpnp_pattern_missed_noti_orange,         // 12 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_ORANGE
	qpnp_pattern_missed_noti_turquoise,      // 13 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_TURQUOISE
	qpnp_pattern_missed_noti_purple,         // 14 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PURPLE
	qpnp_pattern_missed_noti_red,            // 15 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_RED
	qpnp_pattern_missed_noti_lime,           // 16 <- PATTERN_SCENARIO_MISSED_NOTI_REPEAT_LIME
	qpnp_pattern_missed_noti_green_once,     // 17 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_GREEN
	qpnp_pattern_missed_noti_blue_once,      // 18 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_BLUE
	qpnp_pattern_missed_noti_pink_once,      // 19 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PINK
	qpnp_pattern_missed_noti_yellow_once,    // 20 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_YELLOW
	qpnp_pattern_missed_noti_orange_once,    // 21 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_ORANGE
	qpnp_pattern_missed_noti_turquoise_once, // 22 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_TURQUOISE
	qpnp_pattern_missed_noti_purple_once,    // 23 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PURPLE
	qpnp_pattern_missed_noti_red_once,       // 24 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_RED
	qpnp_pattern_missed_noti_lime_once       // 25 <- PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_LIME
};

static inline char* qpnp_pattern_scenario_name(enum qpnp_pattern_scenario scenario)
{
	switch (scenario)
	{
	case PATTERN_SCENARIO_DEFAULT_OFF                   :
		return "PATTERN_SCENARIO_DEFAULT_OFF";
	case PATTERN_SCENARIO_POWER_ON                      :
		return "PATTERN_SCENARIO_POWER_ON";
	case PATTERN_SCENARIO_POWER_OFF                     :
		return "PATTERN_SCENARIO_POWER_OFF";
	case PATTERN_SCENARIO_LCD_ON                        :
		return "PATTERN_SCENARIO_LCD_ON";
	case PATTERN_SCENARIO_CHARGING                      :
		return "PATTERN_SCENARIO_CHARGING";
	case PATTERN_SCENARIO_CHARGING_FULL                 :
		return "PATTERN_SCENARIO_CHARGING_FULL";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_FAVORITE   :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_FAVORITE";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_URGENT     :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_URGENT";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_GREEN      :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_GREEN";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_BLUE       :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_BLUE";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PINK       :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PINK";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_YELLOW     :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_YELLOW";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_ORANGE     :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_ORANGE";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_TURQUOISE  :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_TURQUOISE";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PURPLE     :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_PURPLE";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_RED        :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_RED";
	case PATTERN_SCENARIO_MISSED_NOTI_REPEAT_LIME       :
		return "PATTERN_SCENARIO_MISSED_NOTI_REPEAT_LIME";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_GREEN     :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_GREEN";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_BLUE      :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_BLUE";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PINK      :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PINK";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_YELLOW    :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_YELLOW";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_ORANGE    :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_ORANGE";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_TURQUOISE :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_TURQUOISE";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PURPLE    :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_PURPLE";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_RED       :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_RED";
	case PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_LIME      :
		return "PATTERN_SCENARIO_MISSED_NOTI_ONESHOT_LIME";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_5           :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_5";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_8           :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_8";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_9           :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_9";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_10          :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_10";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_11          :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_11";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_12          :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_12";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_13          :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_13";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_14          :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_14";
	case PATTERN_SCENARIO_HIDDEN_MENU_BLANK_15          :
		return "PATTERN_SCENARIO_HIDDEN_MENU_BLANK_15";

	default :
		break;
	}

	return "PATTERN_SCENARIO_NOT_DEFINED";
}

static ssize_t qpnp_pattern_select(const char* string_format, size_t string_size);
static ssize_t qpnp_pattern_input(const char* string_format, size_t string_size);
static ssize_t qpnp_pattern_blink(const char* string_format, size_t string_size);
static ssize_t qpnp_pattern_onoff(const char* string_format, size_t string_size);
static ssize_t qpnp_pattern_scale(const char* string_format, size_t string_size);

#endif /* __LEDS_QPNP_PATTERN_H_INCLUDED */
