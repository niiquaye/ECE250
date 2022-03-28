#include <bits/c++config.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <map>
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

static void dfs(const graph_t& graph, std::unordered_set<std::string>& visited, std::stack<std::string>& st, const std::string& curr_node){

    visited.insert(curr_node);


    for(const auto& neighbour : graph.at(curr_node)){

         if(visited.find(neighbour) == visited.end()){

            dfs(graph, visited, st, neighbour);

         }

         st.push(curr_node);

    }




}

static std::vector<std::string> Kahns_topological_sort(const graph_t& graph){

    std::vector<std::string> top_sort {};
    std::unordered_set<std::string> visited {};
    std::stack<std::string> stack {};

    for(const auto& nodes : graph)
        dfs(graph, visited, stack, nodes.first);

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
	while(std::getline(fin,line))
	{
        
//       if(line.at(0) != NUMBER_SIGN){
//          node_name = parse(line);
//          adjacency_list.insert({node_name, {}});
//          continue;
//        }else{
//          neighbour = parse(line);
//        }


        adjacency_list.at(node_name).push_back(neighbour);

	}

    std::cout << adjacency_list << std::endl;

    // Kahn's Topological sorting algorithm

    auto top_sort = Kahns_topological_sort(adjacency_list);

    // print out to the console

    for(const auto& node : top_sort)
        std::cout << node << std::endl;


	
	return EXIT_SUCCESS;
}



