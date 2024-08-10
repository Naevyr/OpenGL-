#pragma once

#include <vector>


class IndexBuffer {
    private:
        unsigned int m_glID; 
        unsigned int m_count;  
    public:
        inline IndexBuffer() {}
        IndexBuffer(std::vector<unsigned char> data);
        void Bind();
        inline unsigned int getCount() const { return m_count; }

};