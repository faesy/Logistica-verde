/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
/**************************************************************************************************
 * Implementation of the TAD Node
**************************************************************************************************/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h" // Include of the Edge class

using namespace std;

// Definition of the Node class
class Node{

    // Attributes
    private:
        Edge* first_edge;
        Edge* last_edge;
        int id;
        int degree;
        float weight;
        Node* next_node;

    public:
        // Constructor
        Node(int id);
        // Destructor
        ~Node();
        // Getters
        Edge* getFirstEdge();
        Edge* getLastEdge();
        int getId();
        int getDegree();
        float getWeight();
        Node* getNextNode();
        // Setters
        void setNextNode(Node* node);
        void setRotulo(int rotulo);
        // Other methods
        bool searchEdge(int target_id);
        void insertEdge(int target_id, int rotulo);
        void removeAllEdges();
        int removeEdge(int id,  Node* target_node);
        void incrementDegree();
        void decrementDegree();
        Edge* hasEdgeBetween(int target_id);
        // Auxiliar methods

};

#endif // NODE_H_INCLUDED
