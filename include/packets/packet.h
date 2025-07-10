#ifndef COMMON_PACKET_H
#define COMMON_PACKET_H

#include <cstdint>
#include <cstring>
#include <string>

/**
 * @file packet.h
 * @brief Заголовочный файл с определением структуры пакета для BLE/UART通信
 */

/**
 * @brief Максимальный размер полезных данных в пакете
 * @details Ограничен 512 байтами для оптимизации использования памяти
 *          и совместимости с MTU BLE соединений
 */
constexpr size_t PACKET_DATA_SIZE = 512;

#pragma pack(push, 1) // Гарантируем плотную упаковку структуры

/**
 * @brief Универсальная структура пакета для передачи данных по BLE/UART
 * @details Используется для стандартизированного обмена данными между устройствами.
 *          Все поля имеют четко определенные размеры для кросс-платформенной совместимости.
 *
 * @warning Изменение порядка полей или их размеров требует синхронного обновления
 *          на всех устройствах, участвующих в обмене данными
 */
struct Packet
{
    /**
     * @brief Идентификатор соединения/устройства
     * @details Содержит:
     * - Для BLE: connection ID (возвращаемый в событиях подключения)
     * - Для UART: уникальный ID устройства-отправителя
     * @note Значение 0 зарезервировано для широковещательных сообщений
     */
    uint16_t id;

    /**
     * @brief Размер полезных данных в байтах
     * @details Должен удовлетворять условию: 0 < size <= PACKET_DATA_SIZE
     * @warning Фактическое содержимое data[0..size-1] должно быть инициализировано
     */
    uint16_t size;

    /**
     * @brief Полезные данные пакета
     * @details Максимальная длина определяется PACKET_DATA_SIZE.
     *          Реальная длина данных указывается в поле size.
     *
     * @note Для текстовых данных рекомендуется нуль-терминирование
     * @note Для бинарных данных используйте первые size байт
     */
    uint8_t data[PACKET_DATA_SIZE];

    /**
     * @brief Проверка валидности пакета
     * @return true если 0 < size <= PACKET_DATA_SIZE
     * @return false в противном случае
     *
     * @note Метод не проверяет содержимое data, только границы size
     */
    [[nodiscard]] bool is_valid() const
    {
        return size > 0 && size <= PACKET_DATA_SIZE;
    }

    /**
     * @brief Получить строковое представление заголовка пакета
     * @return std::string Информация о пакете (без данных)
     */
    [[nodiscard]] std::string header_info() const
    {
        return "Packet[id=" + std::to_string(id) +
            ", size=" + std::to_string(size) + "]";
    }

    /**
     * @brief Очистка содержимого пакета
     * @details Обнуляет все поля пакета
     */
    void clear()
    {
        id = 0;
        size = 0;
        memset(data, 0, PACKET_DATA_SIZE);
    }
};

#pragma pack(pop) // Восстанавливаем выравнивание по умолчанию

#endif // COMMON_PACKET_H
