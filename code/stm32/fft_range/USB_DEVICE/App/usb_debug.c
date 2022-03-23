#include "usb_debug.h"
#include "string.h"

#define _INTSIZEOF(n)                   ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define usb_va_start(param_list, head)  (param_list = (param_list_p)&head + _INTSIZEOF(head))
#define usb_va_arg(param_list, type)    (*(type *)(param_list = param_list + _INTSIZEOF(type), param_list- _INTSIZEOF(type)))
#define usb_va_end(param_list)          (param_list = (param_list_p)0)

#define MAX_NUMBER_BYTES (20)

static char hex_tab[]         = "0123456789abcdef";
static char usb_debug_start[] = "[USB_DEBUG]";

static usb_debug_status_e usb_putchar(char character)
{
    char *buf = &character;
    while(CDC_Transmit_FS((uint8_t *)buf, sizeof(char)) != USBD_OK){};

	return USB_DEBUG_OK;
}

static usb_debug_status_e usb_putstring (const char *str)
{
	while (*str != '\0')
	{
		usb_putchar(*str++);
	}

	return USB_DEBUG_OK;
}

static usb_debug_status_e usb_putnum(long val, int base)
{
	char buf[MAX_NUMBER_BYTES + sizeof(char)];
    char *buf_p = (char *)(buf + MAX_NUMBER_BYTES);
    *buf_p = '\0';

    long sign_val = val;
	val = abs(val);

	do
	{
		buf_p--;
		*buf_p = hex_tab[val % base];
	}
	while (((val /= base) != 0) || (buf_p == (char *)(&buf + sizeof(char))));
	
	if (sign_val < 0)
	{
		buf_p--;
		*buf_p = '-';
	}

	return usb_putstring(buf_p);
}


static usb_debug_status_e usb_debug_handle(const char *format, param_list_p param_list)
{
	for(; *format != '\0'; format++)
	{
		if (*format != '%')
        {
			usb_putchar(*format);
			continue;
		}

		format++;

		while (*format >= '0' && *format <= '9')
        {
			format++;
		}
		
		switch (*format)
        {
		    case USB_OCTAL_SYMBOL:
			    {
			    	usb_putnum(usb_va_arg(param_list, unsigned int), USB_OCTAL);
				    break;
			    }
		    case USB_SIGN_DECIMAL_SYMBOL:
			    {
			    	usb_putnum(usb_va_arg(param_list, int), USB_DECIMAL);
				    break;
			    }
		    case USB_UNSIGN_DECIMAL_SYMBOL:
			    {
			    	usb_putnum(usb_va_arg(param_list, unsigned int), USB_DECIMAL);
				    break;
			    }
		    case USB_HEX_SYMBOL:
			    {
			    	usb_putnum(usb_va_arg(param_list, unsigned int), USB_HEX);
				    break;
			    }
		    case USB_CHAR_SYSMBOL:
			    {
				    usb_putchar(usb_va_arg(param_list, int));
				    break;
			    }
		    case USB_STRING_SYSMBOL:
			    {
				    usb_putstring(usb_va_arg(param_list, char *));
				    break;
			    }

		    default:
			    {
				    usb_putchar(*format);
			    }
		    break;
		}
	}
	return USB_DEBUG_OK;
}

usb_debug_status_e USB_DEBUG(const char *format, ...)
{
    usb_putstring(usb_debug_start);
    param_list_p param_list;
	usb_va_start(param_list, format);
	usb_debug_status_e ret = usb_debug_handle(format, param_list);
	usb_va_end(param_list);

	return ret;
}


uint8_t usb_debug_test(void)
{
	USB_DEBUG("USB_DEBUG test\n\r") ;
	USB_DEBUG("test char = %c, %c\n\r", 'Z', 'R');
	USB_DEBUG("test decimal number = %d\n\r", 123456);
	USB_DEBUG("test decimal number = %d\n\r", -123456);
	USB_DEBUG("test hex number = 0x%x\n\r", 0x55aa55aa);
	USB_DEBUG("test string = %s\n\r", "zhangrun_test");
	USB_DEBUG("0x1 = %d\n\r", 0x1);
	USB_DEBUG("16 = %x\n\r", 16);

	return 0;
}
