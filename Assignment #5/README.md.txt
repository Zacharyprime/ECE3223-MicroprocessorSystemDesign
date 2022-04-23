Your program should allow the user to adjust the brightness of LED1 and LED2 using the four
switches. Pressing “L1up” should increase the brightness of LED1, pressing “L1down” should decrease
the brightness of LED1. Likewise, pressing “L2up” should increase the brightness of LED2, pressing
“L2down” should decrease the brightness of LED2. The brightness of the LEDs should be adjusted by
changing the duty cycle of the LEDs from 0% to 100% in steps of 20% per press.
The I2C EEPROM (24LC01 or 24AA01) should be used to store the selected brightness level of both
LEDs so that the last selected brightness will always be restored as the initial default whenever the
program starts. If the contents of the EEPROM are not valid (for example, the EEPROM is blank or has
been somehow corrupted), both LEDs should default to 100% brightness. Note that although the
EEPROM can be rewritten over 1 million times, this can been exceeded if constantly written to for a
few hours; to avoid premature failure, only update the EEPROM when the brightness level is changed.