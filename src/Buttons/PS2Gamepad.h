#ifndef PS2Gamepad_h
#define PS2Gamepad_h

#include "Button.h"
#include "AnalogStick.h"

namespace simpleButton {
    class PS2Gamepad {
        public:
            Button* up               = NULL;
            Button* down             = NULL;
            Button* left             = NULL;
            Button* right            = NULL;
            Button* l1               = NULL;
            Button* l2               = NULL;
            Button* r1               = NULL;
            Button* r2               = NULL;
            Button* select           = NULL;
            Button* start            = NULL;
            Button* square           = NULL;
            Button* triangle         = NULL;
            Button* x                = NULL;
            Button* circle           = NULL;
            AnalogStick* analogLeft  = NULL;
            AnalogStick* analogRight = NULL;

            PS2Gamepad();
            PS2Gamepad(uint8_t clockPin, uint8_t cmdPin, uint8_t attPin, uint8_t dataPin);
            ~PS2Gamepad();

            void setup(uint8_t clockPin, uint8_t cmdPin, uint8_t attPin, uint8_t dataPin);
            void reconfig();

            void update();

            String getError();

            bool connected();

            void setUpdateInterval(uint32_t updateInterval);
            void setMotors(uint8_t motorA, uint8_t motorB);

        private:
            void poll();
            void poll(uint8_t motorA, uint8_t motorB);

            bool getDigitalValue(uint8_t button);
            uint8_t getAnalogValue(uint8_t button);

            // config
            uint8_t motorA = 0x00; // 0 = OFF, 1 = ONN
            uint8_t motorB = 0x00; // 0-39 = OFF, 40 - 255 = ON

            bool rumbleEnabled   = false;
            bool pressureEnabled = false;

            uint32_t updateInterval = 25;

            // class variables
            bool is_connected = false;

            uint8_t errorCode      = 0;
            uint8_t controllerType = 0;
            uint8_t gamepadData[21];

            uint16_t buttonData     = 0;
            uint16_t prevButtonData = 0;

            uint32_t lastPoll = 0;

            uint8_t clockPin = 0;
            uint8_t cmdPin   = 0;
            uint8_t attPin   = 0;
            uint8_t dataPin  = 0;

            // in/output
            uint8_t shift(uint8_t data);

            // commands
            void sendEnter();
            void sendMode();
            void sendRumble();
            void sendBytesLarge();
            void sendExit();
            void sendRead();
    };
}

#endif // ifndef PS2Gamepad_h