# ESP32 Common Utilities

![Лицензия](https://img.shields.io/badge/license-Unlicense-blue.svg)
![PlatformIO](https://img.shields.io/badge/platform-ESP32--C3-green.svg)
![Version](https://img.shields.io/badge/version-0.0.1-orange)

Базовые утилиты для проектов на ESP32:

- Универсальная структура пакетов для BLE/UART
- Оптимизированное выравнивание памяти
- Поддержка ESP32-C3/ESP32-S3

## Установка

### PlatformIO

Добавьте в platformio.ini:

```ini
lib_deps =
    https://github.com/PJ82RU/esp32-common.git
```

### Пример использования

```cpp
#include &#60;esp32_common/packet.h&#62;

Packet packet;

void setup() {
packet.size = sprintf((char*)packet.data, "Hello ESP32!");
}

void loop() {
// Передача пакета
}
```

## Структура пакета

```plaintext
+------+---------------------+
| size | data (512 байт)     |
| 2    | 512                 |
+------+---------------------+

## Лицензия
Public Domain (Unlicense)


### 5. Пример `examples/basic_packet/src/main.cpp`
```cpp
#include <Arduino.h>
#include <esp32_common/packet.h>

void setup() {
  Serial.begin(115200);
  
  Packet tx_pkt;
  tx_pkt.size = snprintf((char*)tx_pkt.data, 
                        PACKET_DATA_SIZE, 
                        "Packet at %lu ms", 
                        millis());
  
  log_d("Created packet: %.*s", tx_pkt.size, tx_pkt.data);
}

void loop() {
  delay(1000);
}