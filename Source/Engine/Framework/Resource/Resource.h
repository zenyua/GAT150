#pragma once
#include <string>
#include <memory>

namespace ringo {
    class Resource {
    public:
        virtual ~Resource() = default;

        virtual bool Create(std::string filename, ...) = 0;
        //bool Load(std::string filename, class Renderer& renderer);
        //virtual bool Load(std::string filename, class Renderer& renderer) = 0;
    };
    
    template <typename T>
    using res_t = std::shared_ptr<T>;
}