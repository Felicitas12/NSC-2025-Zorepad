#pragma once

#include <cstddef>
#include <cstdint>

#include "Export.h"

class UUID
{
public:
	ENGINE_API UUID();
	ENGINE_API UUID(uint64_t uuid);
	ENGINE_API UUID(const UUID&) = default;

	ENGINE_API operator uint64_t() const { return m_UUID; }
private:
	uint64_t m_UUID;

};
namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<UUID>
	{
		std::size_t operator()(const UUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};

}
