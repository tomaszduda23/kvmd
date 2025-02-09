#include "factory.h"
#include "proto.h"
#include "usb/stm32-keyboard.h"
#include "usb/stm32-mouse-win98.h"
#include "usb/stm32-mouse-relative.h"

//TODO find STM32 define
#ifdef ARDUINO_ARCH_AVR
#error "This is supposed to be included only for STM32"
#endif

static USBHID * getUsbHid()
{
	static USBHID hid;
	return &hid;
}

kvmd::Keyboard* kvmd::Factory::makeKeyboard(uint8_t kbd)
{
	switch (kbd) {
#	ifdef HID_WITH_USB
		case PROTO::OUTPUTS1::KEYBOARD::USB:
			//TODO add instance of HID
            return new stm32::UsbKeyboard(getUsbHid());
#	endif
#	ifdef HID_WITH_PS2
		case PROTO::OUTPUTS1::KEYBOARD::PS2:
            return new Ps2Keyboard();
#	endif
	}
	return new Keyboard();
}

kvmd::UsbMouse* kvmd::Factory::makeMouse(uint8_t mouse)
{
	switch (mouse) {
#	ifdef HID_WITH_USB
		case PROTO::OUTPUTS1::MOUSE::USB_ABS:
            return new stm32::UsbMouseAbsolute();
		case PROTO::OUTPUTS1::MOUSE::USB_WIN98:
            return new stm32::UsbMouseAbsoluteWin98();
		case PROTO::OUTPUTS1::MOUSE::USB_REL:
            return new stm32::UsbMouseRelative();
#	endif
	}    
	return new UsbMouse();
}

