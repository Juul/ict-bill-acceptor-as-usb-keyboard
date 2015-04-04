Converting ICT bill acceptor pulse output to USB keyboard keypresses.

# Overview

This guide shows how to connect an ICT bill acceptor with pulse output to an Arduino Leonardo and includes code for the Arduino that will make it act like a USB keyboard, wait until a certain dollar amount has been accepted by the bill acceptor, and send a keypress (e.g. F12). Code is also included to ascertain the pulse width (duration) of your bill acceptor.

This guide assumes you have the following:

* An arduino leonardo (or clone)
* An ICT bill acceptor such as the A6 and A6-II, both DC 12 volts and AC110 volts versions
* A 10k ohm resistor
* Some wire
* Any 12 volt dc power supply (for the 12v DC bill acceptor)
* or a normal grounded 110v AC power cord from e.g. a desktop computer (for 110v AC bill acceptor)
* Soldering iron + solder
* Voltmeter/multimeter

This guide uses the pulse interface from the bill acceptor even though these bill acceptors also have a serial interface (which would probably be faster and better). The ICT bill acceptor pulse output functions similar to someone pressing a button. You have two wires connected between your Arduino and bill acceptor and for every pulse the bill acceptor shorts the wires (connects the two wires together). This guide should work for any bill acceptor or coin acceptor that functions in this manner.

# Pinouts

## 12v DC version 

### Wiring harness pinout

Assuming you have the wiring harness (the short cable sticking out from the bill acceptor and terminating in a 9 pin square connector), use this pinout.

```
    .....
-------------
| 1 | 2 | 3 |
-------------
| 4 | 5 | 6 |
-------------
| 7 | 8 | 9 |
-------------
```

Here are the pins used in this guide:

* 5: 12v DC positive
* 7: Pulse + [hook up to 5v DC on arduino]
* 8: Pulse - [hook up to an input pin on arduino]
* 9: 12v DC negative

Unless you happen to have the matching 9-pin female connector, I recommend cutting the wires for the pins you need (leaving a bit of wire on the plug so it isn't rendered permanently useful, just in case), and solder to the wires.

### Direct pinout

Assuming you don't have the wire harness, use this pinout. 

With the bill acceptor lying on the table with the hole for accepting bills pointed down towards the table and the 30 pins facing towards you, this is the relevant pinout:

```
-----------------------------------------------------------------------------
|  1 |   2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15 |
-----------------------------------------------------------------------------
| 16  | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
-----------------------------------------------------------------------------
```

Only listing pins used in this guide:

* 1: Pulse - [hook up to an input pin on arduino]
* 2: 12v DC positive
* 10: 12v DC negative
* 16: Pulse + [hook up to 5v DC on arduino]

I recommend sliding off the plastic cover below the pin connector and accessing the pins where they are soldered onto the circuit board of the bill acceptor, since it's otherwise quite hard to maneuver a soldering iron (+ you retain the ability to connect a wire harness later). Remember that when looking at the pins from below the PCB the bottom row corresponds to the top row in the diagram and vice-versa.

## 110v AC version

### Wiring harness pinout

```
    .....
-------------
| 1 | 2 | 3 |
-------------
| 4 | 5 | 6 |
-------------
| 7 | 8 | 9 |
-------------
```

Here are the pins used in this guide:

* 4 (black): 110v AC hot
* 5 (green): Ground [from AC power cable]
* 6 (white): 110v AC neutral
* 7 (blue): Pulse + [hook up to 5v DC on arduino]
* 8 (purple): Pulse - [hook up to an input pin on arduino]

### Direct pinout

Assuming you don't have the wire harness, use this pinout. 

With the bill acceptor lying on the table with the hole for accepting bills pointed down towards the table and the 30 pins facing towards you, this is the relevant pinout:

```
-----------------------------------------------------------------------------
|  1 |   2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15 |
-----------------------------------------------------------------------------
| 16  | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
-----------------------------------------------------------------------------
```

Only listing pins used in this guide:

* 1: Pulse - [hook up to an input pin on arduino]
* 4: 110v AC neutral
* 16: Pulse + [hook up to 5v DC on arduino]
* 20: 110v AC hot
* 21: Ground [from AC power cable]

I recommend sliding off the plastic cover below the pin connector and accessing the pins where they are soldered onto the circuit board of the bill acceptor, since it's otherwise quite hard to maneuver a soldering iron (+ you retain the ability to connect a wire harness later). Remember that when looking at the pins from below the PCB the bottom row corresponds to the top row in the diagram and vice-versa.

# Connecting to Arduino

First, choose an input pin on the Arduino. It makes sense to choose one closer to the ground (GND) pin. I used pin 10. Now, on the back of the arduino, solder a 10k resistor between pin 10 and the GND pin. This is to prevent current from flowing into the input pin when the input pin gets connected to +5 volts during pulses.

Now solder a wire from the "pulse +" pin from the bill acceptor to the 5v pin on the arduino. Solder another wire from the "pulse -" pin to the input pin on the arduino (the one with the 10k resistor connected).

## Grounding Arduino

You should also connect the arduino ground pin to the same ground as the bill acceptor, however, if the computer the arduino is plugged into is already grounded to the same ground then it will probably be fine with just the two pulse pins connected.

# Connecting power to bill acceptor

## 12v DC

You can use a normal 12v DC power supply, e.g. from an old DSL modem or wifi router. Cut the barrel jack off and use a multimeter to find out which wire is postive and negative. Solder the positive wire from your 12v DC power supply to the "12v DC positive" pin on the bill acceptor and the negative wire from the power supply to the "12v DC negative" pin on the bill acceptor. One you've done this, plug the 12v power supply into a socket. The bill acceptor should power up, make some noise and the LEDs on the front should start blinking. If it accepts a bill then you did it right.

## 110v AC

Get a three prong power cable, e.g. an old desktop computer cable. Cut the computer end off. Usually the wires will be black, white and green. You should always check with a multimeter but usually black is hot, white is neutral and green is ground. Solder the hot wire to the "110v AC hot" pin on the bill acceptor. Solder the neutral wire to the "110v AC neutral" pin on the bill acceptor. Solder the ground wire to the ground pin on the bill acceptor. Now make sure you insulate all locations where it's possible for anyone or anything to touch exposed 110v AC. I usually use a glue gun to coat everything and then wrap it in electrical tape once the glue is dry. Now plug in the power cable to a wall socket. The bill acceptor should power up, make some noise and the LEDs on the front should start blinking. If it accepts a bill then you did it right.

# Finding the pulse width

Now, different bill acceptors can have different pulse widths (how long each pulse lasts). Some bill acceptors allow you to configure this. I included a simple Arduino program to find the pulse width. 

Plug in the bill acceptor power cable/adapter and connect the arduino to you computer. Start up the arduino software and open the pulse_width_finder.ino file. In the menu, make sure that "Tools -> Serial Port" is set to your arduino's serial port (there's likely just the one option, so select it). In "Tools -> Board" select "Arduino Leonardo". Now hit the upload button (top left, second from left).

The code should upload successfully. Now open "Tools -> Serial Monitor" and insert a bill into your bill acceptor. The serial monitor will show one number for each pulse received. The number is the pulse width (duration) in milliseconds. This will also tell you how many pulses per dollar the bill acceptor sends. This software currently expects one pulse per dollar, so if that's not the case you will have to change the setting on your bill acceptor (probably using the little switches on the side) or change the arduino code.

The pulse widths will probably be slightly different. E.g. between 51 and 54 ms. That's fine. Make a note of it.

# Programming the arduino with bill acceptor software

Now open the bill_acceptor.ino file.

Change the number 10 on the line "#define INPUTPIN (10)" to the number of the pin you used on the arduino. Change the line 

Change the number 40 in the line "min_pulse_width = 40;" to a value about 10 ms below the smallest value you observed in the pulse width finder.

Change the number 60 in the line "max_pulse_width = 60;" to a value about 10 ms higher than the smallest value you observed in the pulse width finder.

Change the number 5 in the line "cost_of_service = 5;" to the number of dollars you want the bill acceptor to require before it sends a keypress to the computer. If you set this value to e.g. 5 and somone puts a 10 dollar bill into the machine, then the computer will still only receive one keypress. If someone inserts 10 one-dollar bills then the keypress will be sent twice (once after each five bills).

Change the value KEY_F12 in the line "Keyboard.write(KEY_F12);" to the value of they key you want the arduino to send when enough money has been received.

Now program your arduino by hitting the upload button.

After successful upload, open a program that will do something when the keypress is sent and insert some bills to verify that the keypress is being sent correctly. 

That's it! You now have a bill acceptor that acts as a usb keyboard!