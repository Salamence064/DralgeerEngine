#pragma once

#include <utility>

namespace Dralgeer {
    // push-pop stack where pop will also return the value popped
    template <typename T>
    class Stack {
        private:
            T* stack = nullptr;
            int count = 0;
            int capacity;

            inline void grow() {
                capacity *= 2;
                T* temp = new T[capacity];

                for (int i = 0; i < count; ++i) { temp[i] = std::move(stack[i]); }

                delete[] stack;
                stack = temp;
            };

        public:
            // Initialize a stack with a specified capacity (default of 16).
            // Specifying a capacity <= 0 will cause undefined behavior.
            Stack(int capacity = 16) : stack(new T[capacity]), capacity(capacity) {};


            // * ==================
            // * Rule of 5 Stuff
            // * ==================
            
            Stack(Stack const &stack) {
                count = stack.count;
                capacity = stack.capacity;
                this->stack = new T[capacity];

                for (int i = 0; i < count; ++i) { this->stack[i] = stack.stack[i]; }
            };

            Stack(Stack &&stack) {
                count = stack.count;
                capacity = stack.capacity;
                this->stack = stack.stack;

                stack.stack = nullptr;
            };

            Stack& operator = (Stack const &stack) {
                if (this != stack) {
                    if (this->stack) { delete[] this->stack; }

                    count = stack.count;
                    capacity = stack.capacity;
                    this->stack = new T[capacity];

                    for (int i = 0; i < count; ++i) { this->stack[i] = stack.stack[i]; }
                }

                return *this;
            };

            Stack& operator = (Stack &&stack) {
                if (this != stack) {
                    count = stack.count;
                    capacity = stack.capacity;
                    this->stack = stack.stack;

                    stack.stack = nullptr;
                }

                return *this;
            };


            // * ==================
            // * Normal Functions
            // * ==================

            // push a new element onto the stack
            inline void push(T const &val) {
                if (capacity == count) { grow(); }
                stack[count++] = val;
            };

            // push a new element onto the stack
            inline void push(T &&val) {
                if (capacity == count) { grow(); }
                stack[count++] = std::move(val);
            };

            // push multiple elements onto the stack
            // do not try to access the elements from the original list after pushing them onto the stack
            inline void push(T* vals, int size) {
                if (count - 1 + size >= capacity) {
                    capacity += size;
                    T* temp = new T[capacity];

                    for (int i = 0; i < count; ++i) { temp[i] = std::move(stack[i]); }

                    delete[] stack;
                    stack = temp;
                }

                for (int i = 0; i < size; ++i) { stack[count++] = std::move(vals[i]); }
            };

            // pop the top element of the stack
            inline T pop() { return std::move(stack[--count]); };
    };

    // static graph used for linking SubScenes together
    // specialized graph which only stores the adjacency matrix as SubScenes can be denoted by their corresponding number
    // all edges for this graph are bidirectional
    class Graph {
        private:
            bool** adjacencyMat;
            int numNodes; // the number of nodes 
            int maxAdj; // max number of adjacent nodes allowed for any given node

        public:
            inline Graph() : adjacencyMat(nullptr), numNodes(0) {};

            /**
             * @brief Create a graph for linking SubScenes together.
             * 
             * @param edges The SubScenes that form an edge with each other. Each inner array must be length 2.
             * @param numEdges The number of edges passed into the graph.
             * @param numNodes The number of nodes the graph will handler.
             * @param maxAdj The max number of adjacent nodes allowed for any given node.
             */
            Graph(int** edges, int numEdges, int numNodes, int maxAdj = 4);


            // * ==================
            // * Rule of 5 Stuff
            // * ==================

            Graph(Graph const &graph);
            Graph(Graph &&graph);
            Graph& operator = (Graph const &graph);
            Graph& operator = (Graph &&graph);
            ~Graph();


            // * ==================
            // * Normal Functions
            // * ==================

            // returns a list of SubScene nodes adjacent to a given SubScene node
            // numAdj will be updated to equal the number of adjacent SubScene nodes
            // remember to use delete[] after you finish using this list
            int* adjacentNodes(int node, int &numAdj);
    };
}
