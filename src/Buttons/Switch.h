#ifndef Switch_h
#define Switch_h

#include "Button.h"
#include "ButtonGPIOExpander.h"

namespace simpleButton {
    class Switch {
        public:
            Button* button = NULL;

            Switch();
            Switch(uint8_t pin);
            Switch(GPIOExpander* pcf, uint8_t pin);
            Switch(Button* button);

            ~Switch();

            void setup(uint8_t pin);
            void setup(GPIOExpander* pcf, uint8_t pin);
            void setup(Button* button);

            void update();
            void update(bool state);

            void setButton(Button* button);

            bool getState();
            bool clicked();

        private:
            bool tmpState = false;
    };
}

#endif // ifndef Switch_h