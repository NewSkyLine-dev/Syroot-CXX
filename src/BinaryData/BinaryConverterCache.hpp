#pragma once

#include <unordered_map>
#include <typeinfo>
#include <memory>

#include "IBinaryConverter.hpp"

namespace Syroot::BinaryData
{
    class BinaryConverterCache
    {
    private:
        // A map to store instances of binary converters.
        static std::unordered_map<std::type_info, std::unique_ptr<IBinaryConverter>> _cache;
    public:
        /** Get an instance of a binary converter for the given type.
        * If an instance does not already exist, it will be created.*/
        static IBinaryConverter *GetConverter(const std::type_info type)
        {
            // Check if an instance of the converter exists in the cache.
            auto it = _cache.find(type);
            if (it == _cache.end())
            {
                // If not, create a new instance of the converter and add it to the cache.
                std::unique_ptr<IBinaryConverter> instance = std::make_unique<IBinaryConverter>(type);
                auto [it, success] = _cache.emplace(type, std::move(instance));
            }

            // Return the instance of the converter from the cache
            return it->second.get();
        }
    };
} // namespace Syroot::BinaryData
