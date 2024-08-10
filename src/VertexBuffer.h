#pragma once

#include <vector>
#include <map>


class VertexBuffer {
    


    private:

    
        unsigned int m_glID;
        unsigned int m_instancedMeshes;
        bool m_isStatic;



        struct DataOffset {
            unsigned int offset;
            unsigned int size;
        };
        std::map<unsigned int,DataOffset> m_offsets;
      

    public:
     
        VertexBuffer(); 
        void Bind() const;
        
        
        unsigned int AddMesh(std::vector<unsigned char>& data);
        void RemoveMesh(unsigned int m_meshID);


        void SetUsage(bool staticBuffer);
        inline bool IsStatic() const {return m_isStatic;}

        ~VertexBuffer();
      
};

