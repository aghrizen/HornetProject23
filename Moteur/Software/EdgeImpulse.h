#ifndef _EDGE_IMPULSE_H
#define _EDGE_IMPULSE_H

/* Includes ---------------------------------------------------------------- */
#include <Hornet_inferencing.h>
#include "edge-impulse-sdk/dsp/image/image.hpp"

#include "esp_camera.h"
#include "FrelonKiller.h"

EdgeImpulseAnswer EdgeImpulse();
bool ei_camera_init(void);
void ei_camera_deinit(void);
bool ei_camera_capture(uint32_t img_width, uint32_t img_height, uint8_t *out_buf) ;



#endif