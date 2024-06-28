#pragma once

class VertexBuffer {

    private:
        unsigned int m_glID;
  
    public:
        inline VertexBuffer() {}
        VertexBuffer(void * data, unsigned int size); 


        void bind() const;
        void update(float* data, int size);
};