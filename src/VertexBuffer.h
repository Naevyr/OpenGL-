#pragma once

class VertexBuffer {

    private:
        unsigned int m_glID;
  
    public:
        inline VertexBuffer() {}
        VertexBuffer(void * data, unsigned int size); 


        void Bind() const;
        
        void Update(float* data, int size);
};