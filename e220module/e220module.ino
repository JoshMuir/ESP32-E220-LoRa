#include <SoftwareSerial.h>

#define BROADCAST_ADDRESS 0xFFFF
#define MONITOR_ADDRESS 0x0000

//#define READER
// #define TRANSMITTER

// Constants
static const uint8_t MIN_CHANNEL = 0;
static const uint8_t MAX_CHANNEL = 80;
static const float BASE_FREQ = 850.125; // MHz

// Register addresses and configuration enums
enum RegAddress {
    REG_ADDH = 0x00,
    REG_ADDL = 0x01,
    REG_0 = 0x02,
    REG_1 = 0x03,
    REG_2 = 0x04,
    REG_3 = 0x05,
    REG_CRYPT_H = 0x06,
    REG_CRYPT_L = 0x07
};

enum UARTBaudRate {
    UART_1200 = 0b000,
    UART_2400 = 0b001,
    UART_4800 = 0b010,
    UART_9600 = 0b011,
    UART_19200 = 0b100,
    UART_38400 = 0b101,
    UART_57600 = 0b110,
    UART_115200 = 0b111
};

enum SerialParity {
    PARITY_8N1 = 0b00,
    PARITY_8O1 = 0b01,
    PARITY_8E1 = 0b10
};

enum AirDataRate {
    AIR_2400 = 0b000,
    AIR_4800 = 0b001,
    AIR_9600 = 0b010,
    AIR_19200 = 0b011,
    AIR_38400 = 0b100,
    AIR_62500 = 0b101
};

enum modes_t {
    Transmission_Mode = 0b00,
    WOR_Transmit_Mode = 0b01,
    WOR_Receive_Mode = 0b10,
    Config_Mode = 0b11
}

class E220Module {
private:
    SoftwareSerial& serial;
    const int m0Pin;
    const int m1Pin;

    void writeRegister(uint8_t addr, uint8_t value) {
        serial.write(0xC0);
        serial.write(addr);
        serial.write(0x01);
        serial.write(value);
        delay(100);
        
        while(serial.available()) {
            serial.read(); // Clear response
        }
    }

    bool isValidChannel(uint8_t channel) {
        return channel >= MIN_CHANNEL && channel <= MAX_CHANNEL;
    }

public:
    // Constructor
    E220Module(SoftwareSerial& ser, int m0, int m1) : 
        serial(ser), m0Pin(m0), m1Pin(m1) {
        pinMode(m0Pin, OUTPUT);
        pinMode(m1Pin, OUTPUT);
    }

    void setMode(modes_t mode) {
        digitalWrite(m0Pin, mode & 0x01);
        digitalWrite(m1Pin, mode & 0x02);
    }

    // Address configuration
    void setAddress(uint16_t address) {
        uint8_t high = (address >> 8) & 0xFF;
        uint8_t low = address & 0xFF;
        writeRegister(REG_ADDH, high);
        writeRegister(REG_ADDL, low);
    }

    // UART configuration
    void setUARTConfig(UARTBaudRate baud, SerialParity parity, AirDataRate airRate) {
        uint8_t reg0 = (baud << 5) | (parity << 3) | airRate;
        writeRegister(REG_0, reg0);
    }

    // Channel configuration
    bool setChannel(uint8_t channel) {
        if (!isValidChannel(channel)) {
            return false;
        }
        writeRegister(REG_2, channel);
        return true;
    }

    float getFrequency(uint8_t channel) {
        if (!isValidChannel(channel)) {
            return -1;
        }
        return BASE_FREQ + (channel * 1.0);
    }

    bool setChannelByFrequency(float targetFreq) {
        if (targetFreq < BASE_FREQ || targetFreq > (BASE_FREQ + MAX_CHANNEL)) {
            return false;
        }
        uint8_t channel = round(targetFreq - BASE_FREQ);
        return setChannel(channel);
    }

    // Other configurations
    void setRSSIAmbientNoise(bool enable) {
        writeRegister(REG_1, enable ? 0x01 : 0x00);
    }

    void setEncryptionKey(uint16_t key) {
        uint8_t high = (key >> 8) & 0xFF;
        uint8_t low = key & 0xFF;
        writeRegister(REG_CRYPT_H, high);
        writeRegister(REG_CRYPT_L, low);
    }

    // Helper methods
    void configureDefault() {
        setMode(Config_Mode);
        setAddress(0x1234);
        setUARTConfig(UART_9600, PARITY_8N1, AIR_2400);
        setRSSIAmbientNoise(false);
        setChannel(4);
        setMode(Transmission_Mode);
    }


};


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

void loop()
{
#ifdef READER
    delay(500);
    if(mySerial.available()) {
        char* c = mySerial.read();
        Serial.print(c);
    }
#endif
#ifdef TRANSMITTER
    delay(10000);
    mySerial.write("Hello, World!");
#endif

}