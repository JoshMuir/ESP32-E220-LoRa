# E32 Radio Module Register Documentation

## Register Map Overview

| Address | Access | Name | Description | Default |
|---------|--------|------|-------------|---------|
| 0x00 | R/W | ADDH | High byte of module address | 0x00 |
| 0x01 | R/W | ADDL | Low byte of module address | 0x00 |
| 0x02 | R/W | REG0 | UART and Rate Configuration | - |
| 0x03 | R/W | REG1 | Sub-packet Settings and Other Configuration | - |
| 0x04 | R/W | REG2 | Channel Control (CH) | - |
| 0x05 | R/W | REG3 | RSSI and Transmission Settings | - |
| 0x06 | W | CRYPT_H | Key high byte (Write only) | 0x00 |
| 0x07 | W | CRYPT_L | Key low byte (Write only) | 0x00 |

## Detailed Register Descriptions

### REG0 (0x02) - UART and Rate Configuration

#### UART Serial Port Rate (bits 7-5)
| Value | Baud Rate |
|-------|-----------|
| 000 | 1200 bps |
| 001 | 2400 bps |
| 010 | 4800 bps |
| 011 | 9600 bps (default) |
| 100 | 19200 bps |
| 101 | 38400 bps |
| 110 | 57600 bps |
| 111 | 115200 bps |

#### Serial Parity Bit (bits 4-3)
| Value | Parity |
|-------|---------|
| 00 | 8N1 (default) |
| 01 | 8O1 |
| 10 | 8E1 |
| 11 | 8N1 |

#### Air Data Rate (bits 2-0)
| Value | Rate |
|-------|------|
| 000 | 0.3k bps |
| 001 | 1.2k bps |
| 010 | 2.4k bps |
| 011 | 4.8k bps (default) |
| 100 | 9.6k bps |
| 101 | 19.2k bps |
| 110 | 38.4k bps |
| 111 | 62.5k bps |

### REG1 (0x03) - Sub-packet Settings and Other Configuration

#### Sub-Packet Length (bits 7-6)
| Value | Length |
|-------|--------|
| 00 | 240 bytes (default) |
| 01 | 128 bytes |
| 10 | 64 bytes |
| 11 | 32 bytes |

#### RSSI Ambient Noise Enable (bit 5)
| Value | Function |
|-------|----------|
| 0 | Disable (default) |
| 1 | Enable |

#### Transmitting Power (bits 2-1)
| Value | Power |
|-------|-------|
| 00 | 30dBm (default) |
| 01 | 27dBm |
| 10 | 24dBm |
| 11 | 21dBm |

### REG2 (0x04) - Channel Control
- Channel frequency = Base Frequency + CH * 1MHz
- Valid range: 0-83 (total of 84 channels)

### REG3 (0x05) - RSSI and Transmission Settings

#### RSSI Byte Enable (bit 7)
| Value | Function |
|-------|----------|
| 0 | Disable (default) |
| 1 | Enable |

#### Transmission Method (bit 6)
| Value | Mode |
|-------|------|
| 0 | Transparent transmission (default) |
| 1 | Fixed transmission |

#### LBT Enable (bit 4)
| Value | Function |
|-------|----------|
| 0 | Disable (default) |
| 1 | Enable |

#### WOR Cycle (bits 3-0)
| Value | Period |
|-------|--------|
| 000 | 500ms |
| 001 | 1000ms |
| 010 | 1500ms |
| 011 | 2000ms |
| 100 | 2500ms |
| 101 | 3000ms |
| 110 | 3500ms |
| 111 | 4000ms |

## Important Notes

1. **Module Address (ADDH/ADDL)**:
   - When set to 0xFFFF, acts as broadcast/monitor address
   - Module will not perform address filtering in this mode

2. **Channel Configuration**:
Actual frequency = 850.125 + CH *1MHz
   - Channels are spaced 1MHz apart
   - Valid range is 0-80 (total of 81 channels)
   - Default channel is 0 (433.125 MHz)

2. **UART Configuration**:
   - Communicating modules can have different baud rates
   - Recommended to use same baud rate for both parties
   - Consider data congestion with large packets

3. **Air Data Rate**:
   - Must be same for both communicating parties
   - Higher rates = lower delay but shorter transmission distance

4. **LBT (Listen Before Talk)**:
   - Maximum stay time is 2 seconds
   - Helps avoid interference but may cause delays

5. **WOR (Wake on Radio)**:
   - Only valid for mode 1
   - Longer intervals = lower power consumption but higher delay
   - Both sender and receiver must agree on timing