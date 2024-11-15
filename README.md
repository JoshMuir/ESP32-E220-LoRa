### E220Module Class Documentation

The E220Module class provides an interface for configuring and controlling the E220-900T22D wireless module.

## Overview

The E220Module class provides an interface for configuring and controlling the E220-900T22D wireless module.

## Hardware Requirements

- E220-900T22D module
- Arduino running on 5v
- 3.3V power source
- 5V power source
- GPIO Level Translator

## Wiring Diagram

```
    Module                      5v Arduino

    GND  ------------------------ ground
    VCC  ------------------------ +5V
    AUX  3V3---[LVL TRANSLATOR]-- AUX_PIN
    TXD  ------------------------ RX_PIN
    RXD  3V3---[LVL TRANSLATOR]-- TX_PIN
    M1   3V3---[LVL TRANSLATOR]-- M1_PIN
    M0   3V3---[LVL TRANSLATOR]-- M0_PIN

```

## Important Notes

- Ensure proper voltage levels (3.3V/5V) are used
- MI and MO pins can be left unconnected

#### Basic Setup
```cpp
#include <SoftwareSerial.h>

// Create SoftwareSerial instance
SoftwareSerial mySerial(10, 11); // RX, TX pins

// Create E220Module instance
E220Module radio(mySerial, 2, 3); // Serial, M0 pin, M1 pin

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  mySerial.begin(9600);
  
  // Use default configuration
  radio.configureDefault();
}
```

#### Address Configuration
```cpp
// Set module address to 0x1234
radio.setAddress(0x1234);

// Set broadcast address
radio.setAddress(0xFFFF);
```

#### UART Configuration
```cpp
// Configure for 9600 baud, 8N1, 2.4k air rate
radio.setUARTConfig(UART_9600, PARITY_8N1, AIR_2400);

// Configure for high speed communication
radio.setUARTConfig(UART_115200, PARITY_8N1, AIR_62500);
```

#### Channel Configuration
```cpp
// Set channel directly (0-80)
radio.setChannel(9); // 859.125 MHz

// Set channel by frequency
radio.setChannelByFrequency(859.125);

// Get frequency for channel
float freq = radio.getFrequency(9); // Returns 859.125
```

#### Security Configuration
```cpp
// Set encryption key
radio.setEncryptionKey(0xABCD);

// Enable RSSI ambient noise detection
radio.setRSSIAmbientNoise(true);
```

#### Complete Example
```cpp
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);
E220Module radio(mySerial, 2, 3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  // Custom configuration
  radio.setAddress(0x1234);
  radio.setUARTConfig(UART_9600, PARITY_8N1, AIR_2400);
  radio.setChannel(9);
  radio.setEncryptionKey(0xABCD);
  radio.setRSSIAmbientNoise(true);
}

void loop() {
  // Your communication code here
}
```

### Configuration Options

#### UART Baud Rates
- `UART_1200`: 1200 bps
- `UART_2400`: 2400 bps
- `UART_4800`: 4800 bps
- `UART_9600`: 9600 bps (default)
- `UART_19200`: 19200 bps
- `UART_38400`: 38400 bps
- `UART_57600`: 57600 bps
- `UART_115200`: 115200 bps

#### Serial Parity
- `PARITY_8N1`: 8N1 (default)
- `PARITY_8O1`: 8O1
- `PARITY_8E1`: 8E1

#### Air Data Rates
- `AIR_2400`: 2.4k bps (default)
- `AIR_4800`: 4.8k bps
- `AIR_9600`: 9.6k bps
- `AIR_19200`: 19.2k bps
- `AIR_38400`: 38.4k bps
- `AIR_62500`: 62.5k bps