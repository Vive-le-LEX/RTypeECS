/*
 * Copyright (c) 2023 - Kleo
 * Authors:
 * - LEO VILTARD <leo.viltard@epitech.eu>
 * NOTICE: All information contained herein is, and remains
 * the property of Kleo © and its suppliers, if any.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Kleo ©.
*/

#pragma once

#include <bitset>
#include <cinttypes>

namespace EpiCS {

#pragma region ComponentsTypes

    using ComponentType = std::uint8_t;

    const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;

#pragma endregion ComponentsTypes

#pragma region EntityTypes
    using Entity = std::uint64_t;

    const Entity MAX_ENTITIES = 5000;
#pragma endregion EntityTypes

} // namespace EpiCS
