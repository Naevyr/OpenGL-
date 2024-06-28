#pragma once


class IndexBuffer {
    private:
        unsigned int m_glID; 
        unsigned int m_count;  
    public:
        inline IndexBuffer() {}
        IndexBuffer(void * data, unsigned int count);
        void Release();
        

        void bind();
        inline unsigned int getCount() const { return m_count; }

};