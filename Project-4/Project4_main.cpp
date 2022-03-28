#include <bits/c++config.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

// constants
static constexpr std::size_t LINE_LEN {10};
static constexpr char NUMBER_SIGN {'#'};

// aliases
using graph_t =  std::unordered_map<std::string, std::vector<std::string>>;

// Data structures for top sort
static graph_t adjacency_list {};
static std::unordered_set<std::string> visited {};

// operator overload of the << operator for printing adjacency lists
static std::ostream& operator<<(std::ostream& out, graph_t const& graph)
{


   for(const auto& pair : graph){
       out << pair.first <<": ";
       for(const auto& value : pair.second){
          out << value << " ";
       }

       std::cout << "" << std::endl;
   }

    return out;
}

// helper function to parse individual lines extracted from
// the input file
inline static std::string parse(const std::string& line){
    std::string node_name {};
    if(line.at(0) != NUMBER_SIGN){
       for(const auto& c : line){
         node_name.push_back(c);
      }
    }
    else{
      node_name = line.substr(LINE_LEN, line.size()-1);
      node_name.pop_back();

    }
    return node_name;

}

// helper function that runs DFS that generates a topological sort by putting nodes into a stack
// when it backtracks. The function populates the 'st' with a topological sort of the graph
static void dfs( graph_t& graph, std::unordered_set<std::string>& visited, std::stack<std::string>& st, const std::string& curr_node){

    visited.insert(curr_node);


    for(const auto& neighbour : graph.at(curr_node)){

         if(visited.find(neighbour) == visited.end()){

            dfs(graph, visited, st, neighbour);

         }

    }
    st.push(curr_node);



}

// topological sort - runs a dfs over every node while generating 
// the toplogical sort by the stack that is passed by reference into the
// 'dfs' helper function. The topological sort is extracted from the stack
// and populates the return vector with the topological sort. 
static std::vector<std::string> topological_sort(graph_t& graph){

    std::vector<std::string> top_sort {};
    std::unordered_set<std::string> visited {};
    std::stack<std::string> stack {};

    for(const auto& nodes : graph){
       if(visited.find(nodes.first) == visited.end()) 
          dfs(graph, visited, stack, nodes.first);

    }
   
    while(!stack.empty()){
          top_sort.push_back(stack.top());
          stack.pop();
    }
    return top_sort;
}

int main(int argc, char** argv)
{
	//first input argument is always the program name...
	char* fileName = argv[1];
	
	//open the file
	std::ifstream fin(fileName);
	
	if(!fin)
	{
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}

    // construct graph
	std::string line;
    std::string node_name {};
    std::string neighbour {};
    std::unordered_set<std::string> set {};
    // parse file to get node names
	while(std::getline(fin,line))
	{
        
        auto node_name = parse(line);
        if(set.find(node_name) == set.end()){
           adjacency_list.insert({node_name, {}});
           set.insert(node_name);
        }

	}

    std::string child {};
	std::ifstream in(fileName);
    // parse file to get parent - child relation
    while(std::getline(in, line))
    {

       if(line.at(0) != NUMBER_SIGN){
         child = parse(line);
         continue;
       }
       adjacency_list.at(parse(line)).push_back(child);
    }

    std::cout << adjacency_list << std::endl;
    // topological sorting algorithm
    auto top_sort = topological_sort(adjacency_list);

   // print out topological sort the console
   for(const auto& node : top_sort)
        std::cout << node << std::endl;


	
	return EXIT_SUCCESS;
}



