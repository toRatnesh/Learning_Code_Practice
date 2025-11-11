/*****

  References
  episode https://www.youtube.com/watch?v=VzDMgStcCGs


  This example demonstrates about C++17 node_type for containers if applicable
  for a container since c++17 we can perform operation with node of containers

 **********/

#include <map>
#include <print>
#include <set>
#include <string>

int main() {

	{
		std::println("=== map merge() ===");
		std::map<std::string, std::string> original_map{{"k1", "v1"},
			{"k2", "v2"},
			{"k3", "v3"},
			{"k4", "v4"},
			{"k5", "v5"}};
		std::map<std::string, std::string> new_map;
		std::println("before merge()");
		std::println("original map size: {} elements: {}", original_map.size(),
				original_map);
		std::println("new map size: {} elements: {}", new_map.size(), new_map);

		new_map.merge(original_map);
		std::println("after merge()");
		std::println("original map size: {} elements: {}", original_map.size(),
				original_map);
		std::println("new map size: {} elements: {}", new_map.size(), new_map);
	}

	{
		std::println("\n=== map extract() ===");
		std::map<std::string, std::string> original_map{{"k1", "v1"},
			{"k2", "v2"},
			{"k3", "v3"},
			{"k4", "v4"},
			{"k5", "v5"}};
		std::map<std::string, std::string> new_map;
		std::println("before extract()");
		std::println("original map size: {} elements: {}", original_map.size(),
				original_map);
		std::println("new map size: {} elements: {}", new_map.size(), new_map);

		auto l_node = original_map.extract("k2");
		new_map.insert(std::move(l_node));
		new_map.insert(original_map.extract(std::next(original_map.begin())));

		std::println("after merge()");
		std::println("original map size: {} elements: {}", original_map.size(),
				original_map);
		std::println("new map size: {} elements: {}", new_map.size(), new_map);
	}

	{
		std::println("\n=== using node for std::multiset ====");

		std::multiset<std::string> lset{"s1", "s2", "s3", "s4", "s5"};
		std::println("set size: {} elements: {}", lset.size(), lset);

		auto l_node = lset.extract("s2");
		// std::println("Node key: {} value: {}", l_node.key(),
		// l_node.value());
		std::println("Node value: {}", l_node.value());
		l_node.value() = "s2-updated";
		std::println("Node value: {}", l_node.value());

		lset.insert(std::move(l_node));
		std::println("set size: {} elements: {}", lset.size(), lset);
	}

	{
		std::println("\n=== using std::multiset ====");

		std::multiset<std::string> lset{"s1", "s2", "s3", "s4", "s5"};
		std::println("set size: {} elements: {}", lset.size(), lset);

		lset.erase("s2");
		lset.insert("s2-updated");

		std::println("set size: {} elements: {}", lset.size(), lset);
	}

	return 0;
}

/*****
  END OF FILE
 **********/
