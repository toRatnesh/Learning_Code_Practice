/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis

Chapter 25 Container Extensions

25.1 Container-Support of Incomplete Types
	Since C++17 std::vector, std::list, and std::forward_list are required to support incomplete types
	Check: https://drdobbs.com/the-standard-librarian-containers-of-inc/184403814
	
*************/

#include <iostream>
#include <vector>
#include <string>

class Node {
    std::string         m_sval;
    std::vector<Node>   m_nvec;
    public:
    Node(std::string str) : m_sval{str}, m_nvec{} {}
    bool addNode(Node node) { 
        m_nvec.push_back(std::move(node));
        return true; 
    }
    Node & operator[](std::size_t idx) { return m_nvec.at(idx); }
    void display(int indent = 0) const {
        std::cout << std::string(indent, ' ') << m_sval << '\n';
        for(const auto & node : m_nvec) {
            node.display(indent+2);
        }
    }
};

int main() {
    Node root{"root"};
    root.addNode(Node{"series-1"});
    root.addNode(Node{"series-2"});
    root[0].addNode(Node{"series-1-1"});
    root[0].addNode(Node{"series-1-2"});
    root[1].addNode(Node{"series-2-1"});
    root[1][0].addNode(Node{"series-2-1-1"});
    root[1].addNode(Node{"series-2-2"});

    root.display(1);

    return 0;
}

/**********
    END OF FILE
*************/


