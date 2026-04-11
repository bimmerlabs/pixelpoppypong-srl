#pragma once

#define PPP_LOGO_TIMER (17 * 60)
#define PPP_MOSAIC_TIMER (9 * 60)
#define PPP_NBG0_INC 1
#define PPP_NBG1_INC 1
#define PPP_NBG1_MIN 0

extern unsigned int g_LogoTimer;

#ifdef __cplusplus
extern "C" {
#endif

void pppLogo_init(void);
void pppLogo_input(void);
void pppLogo_update(void);
void pppLogo_draw(void);
void update_light_position(void);

#ifdef __cplusplus
}
#endif