#ifndef COMMON_PACKET_H
#define COMMON_PACKET_H

#include <Arduino.h>

constexpr size_t BLE_PACKET_DATA_SIZE = 512;

#pragma pack(push, 1)
/**
 * @brief Универсальная структура пакета для BLE/UART
 */
struct Packet {
    uint16_t size;                       // Размер полезных данных
    uint8_t data[BLE_PACKET_DATA_SIZE];  // Полезные данные
};
#pragma pack(pop)

#endif // COMMON_PACKET_H