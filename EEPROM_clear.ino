/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/

void setup() {
    for (int i = 0; i <= EEPROM.length(); i++) {
    EEPROM.write(i,0);
    }
}

void loop() {
}
