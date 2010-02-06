#ifndef DETECTMAC_H
#define DETECTMAC_H

#include "gluoninput.h"
#include "code.h"
#include "inputdevice.h"
#include "joystick.h"
#include "detectabstract.h"
#include "keyboard.h"
#include "mouse.h"
#include "tablet.h"

#include <QtCore/QObject>
#include <QtCore/QList>

#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{
	class GLUONINPUTSHARED_EXPORT DetectMac : public DetectAbstract
	{
		Q_OBJECT
		
	public:
		DetectMac(QObject * parent);
		~DetectMac();
		
		void searchDevice();
		void setAllEnabled();
		void setAllDisabled();
		
		QList<InputDevice *> getInputList();    
		QList<KeyBoard *> getKeyboardList();
		QList<Mouse *> getMouseList();
		QList<Joystick *> getJoystickList();
		QList<Tablet *> getTabletList();
		QList<InputDevice *> getUnknownDeviceList();    
		
		void addInput(InputDevice *i);
		void addKeyboard(InputDevice *i);
		void addMouse(InputDevice *i);
		void addJoystick(InputDevice *i);
		void addTablet(InputDevice *i);
		void addUnknown(InputDevice *i);
		void clear();
		
	private:
		static void createDevices(const void *value, void *context);
		CFMutableDictionaryRef createMatchingDictionary(UInt32 pUsagePage, UInt32 pUsage);
		
		IOHIDManagerRef deviceManager;
		CFSetRef devices;
	};
}
#endif