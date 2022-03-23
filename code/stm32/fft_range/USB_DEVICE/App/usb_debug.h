#ifndef APP_USB_DEBUG_H_
#define APP_USB_DEBUG_H_

#include "main.h"
#include "usbd_cdc_if.h"

typedef enum
{
	USB_DEBUG_OK = 0,
	USB_DEBUG_FAIL,
} usb_debug_status_e;

typedef enum
{
	USB_OCTAL_SYMBOL          = 'o',
	USB_SIGN_DECIMAL_SYMBOL   = 'd',
	USB_UNSIGN_DECIMAL_SYMBOL = 'u',
	USB_HEX_SYMBOL            = 'x',
	USB_CHAR_SYSMBOL          = 'c',
	USB_STRING_SYSMBOL        = 's',
	USB_POINTER_SYSMBOL       = 'p',

	USB_OCTAL   = 8,
	USB_DECIMAL = 10,
	USB_HEX     = 16,
} usb_number_format_e;

typedef char * param_list_p;
uint8_t USB_DEBUG(const char *fmt, ...);
uint8_t usb_debug_test(void);

#endif /* APP_USB_DEBUG_H_ */
