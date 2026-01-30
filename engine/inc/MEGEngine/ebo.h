#ifndef EBO_H
#define EBO_H

#include <vector>

namespace MEGEngine {
    class EBO {
    public:
        unsigned int ID;
        EBO(const std::vector<unsigned int>& indices);

        void bind();
        void unbind();
        void del();

    };
}

#endif //EBO_H