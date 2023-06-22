# rot13labs fox

Much of this code was copied from / inspired by Yet Another Foxbox (YAFB) by Gregory Stoike (KN4CK) which can be found here: https://github.com/N8HR/YAFB. It has been stripped down and adapted for use on a Seeed Studio XIAO ESP32C3 and a NiceRF SA868.

All credit for this project goes to Gregory Stoike; I just made his work simple enough for my own simple foxes.

## Hardware

The hardware for this fox is (purposely) super simplistic. I wanted something that was minimal to make but could be expanded out by myself or others to do more than just the basic functionality of a fox.

The seed XIAO fit this bill perfectly; it has a battery controller built in to manage the LiPo, reducing the need for more components, and offers wifi and bluetooth for future expandability.

LEDs were added to the radio power and transmit pins for easy troubleshooting.

The full circuit looks like this:

<img src='https://rot13labs.com/images/fox-circuit.png' alt='rot13labs fox circuit diagram' width='400' />

## Firmware

Right now this project is basically just a hodge-podge of others code brought together by a bit of my own.

I tried to comment as liberally as possible because im hoping others can use this code to help their own SA868 projects. It's an awesome chip and deserves a lot more of a community than it currently has.

## Contact

If you found one of my foxes at a con and want help updating the firmware, or are just looking to build one of your own, please feel free to reach out to me on twitter!
@c0ldbru

