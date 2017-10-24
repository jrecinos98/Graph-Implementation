// FILE: graph.cpp (part of the namespace main_savitch_15)
// TEMPLATE CLASS IMPLEMENTED: graph<Item> (See graph.h for documentation.)
// This file is included in the header file and not compiled separately.
// INVARIANT for the graph class:
//   1. The number of vertices in the graph is stored in the member variable
//      many_vertices.
//   1. These vertices are numbered from 0 to many_vertices-1.
//   2. edges is the adjacency matrix for the graph (with true in edges[i][j]
//      to indicate an edge from vertex i to vertex j).
//   3. For each i < many_vertices, labels[i] is the label of vertex i.

//Matt Gottlieb, Jose Recinos

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides size_t
#include <set>        // Provides set
using std::size_t;

namespace main_savitch_15
{
    template <class Item>
    graph<Item>::graph ( ) : many_vertices(0) {
        // intentionally empty
    }

    template <class Item>
    graph<Item>::graph(size_t initial_allocation){
      allocated= initial_allocation;
      edges= new bool*[allocated];
      for (size_t i=0; i< allocated; i++){
	edges[i]= new bool [allocated];
      }
      for (size_t i=0; i<allocated; i++){
	for (size_t j=0; j < allocated; j++){
	  edges[i][j]=false;
	}
      }
      many_vertices= 0;
      labels= new Item[allocated];
    }
  
   
    template <class Item>
    graph<Item>::graph(const graph &source){
      if (source.size() != size()){
	bool **temp= new bool*[source.size()];
	for (size_t i=0; i < source.size();++i){
	  temp[i]= new bool [source.size()];
	  delete [] edges[i];
	}
	edges=temp;
	allocated= source.size();
      }
	
      for (size_t i=0; i < allocated; i++){
	  for (size_t j=0; j < allocated;  ++j){
	    edges[i][j]= source.is_edge(i,j);}
      }
      for (size_t i=0; i < allocated; ++i){
	labels[i]= source[i];
      }
      many_vertices= source.size();
    }
      
      
  //template <class Item>
    // graph<Item>& graph<Item>::operator = (const graph &source){return}
      
    template <class Item>
    graph<Item>::~graph(){
      for(size_t i=0; i < allocated; i++){
	//for (int j=0; j < allocated; j++)
	delete [] edges[i];
      }
      delete [] edges;
    }

    template <class Item>
    void graph<Item>::resize(size_t new_allocation){
      if (new_allocation > size()){
	bool **temp= new bool*[new_allocation];
	Item *temp2= new Item [new_allocation];
	for (size_t i=0; i < new_allocation;++i){
	  temp[i]= new bool [new_allocation];	  
	}
	for (size_t i=0; i < allocated; i++){
	  temp2[i]= labels[i];
	  for (size_t j=0; j < allocated;  ++j){
	    temp[i][j]=edges[i][j];
	   
	  }
	  delete [] edges[i];
	}
	delete [] labels;
	labels= temp2;
	for (size_t i=allocated; i<  new_allocation; ++i){
	  for (size_t j=0; j < new_allocation;  ++j){
	    temp[i][j]= false;
	  }
	}
	edges=temp;
	allocated= new_allocation;
	
      }
    }
 

    template <class Item>
    void graph<Item>::add_edge(size_t source, size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = true;

    }

    template <class Item>
    void graph<Item>::add_vertex(const Item& label)
    // Library facilities used: cassert, cstdlib
    {
        size_t new_vertex_number;
        size_t other_number;

        if (size( ) < allocated){
	  resize(allocated*2);
	}
        new_vertex_number = many_vertices;
        many_vertices++;
        for (other_number = 0; other_number < many_vertices; ++other_number)
        {
            edges[other_number][new_vertex_number] = false;
            edges[new_vertex_number][other_number] = false;
        }
        labels[new_vertex_number] = label;
    }

  
    
    template <class Item>
    bool graph<Item>::is_edge(size_t source, size_t target) const
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        return edges[source][target];
    }

    template <class Item>
    Item& graph<Item>::operator[ ] (size_t vertex)
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns a reference to the label
    }

    template <class Item>
    Item graph<Item>::operator[ ] (size_t vertex) const
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns only a copy of the label
    }

    template <class Item>
    std::set<size_t> graph<Item>::neighbors(size_t vertex) const
    // Library facilities used: cassert, cstdlib, set
    {
        std::set<size_t> answer;
        size_t i;

        assert(vertex < size( ));

        for (i = 0; i < size( ); ++i)
        {
            if (edges[vertex][i])
                answer.insert(i);
        }
        return answer;
    }

    template <class Item>
    void graph<Item>::remove_edge(size_t source, size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = false;
    }
}
