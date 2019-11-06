#include<fmt/printf.h>
#include<vector>
#include<string>
#include<optional>
#include<range/v3/algorithm/for_each.hpp>
#include<map>
#define MAKE_BUFF_TREES_FUNC_DEBUG

std::vector<std::vector<std::string>> test_copy_tokens{ {"A1","0","M","0","A1.lenth"},
														{"A2","0","M","0","A1.lenth"},
														{"A3","0","M","0","A1.lenth"},
														{"A4","0","M2","0","A1.lenth"},
														{"A5","0","M2","0","A1.lenth"}
														,{"A6","0","M3","0","A1.lenth"} };

auto print_map = [](std::pair<size_t, std::string> p) {
	fmt::print("{} : {}\n", p.first, p.second);
};


std::optional<std::vector< std::map<size_t, std::string> > > make_buff_tree(const std::vector<std::vector<std::string>>& copy_tokens);

std::optional<std::vector< std::map<size_t, std::string> > > make_buff_tree(const std::vector<std::vector<std::string>>& copy_tokens)
{
	std::vector<std::string> main_tokens;
	main_tokens.reserve(20);
	for (const auto& var : copy_tokens)
	{
		main_tokens.push_back(var[2]);
	}
	main_tokens.erase(std::unique(main_tokens.begin(), main_tokens.end()), main_tokens.end());

	std::map<size_t, std::string> buff_tree;
	std::vector< std::map<size_t, std::string> > buff_trees_vector;
	const auto main_tokens_size = main_tokens.size();
	if (main_tokens_size == 0)
	{
		return (std::nullopt);
	}
	else
	{
		buff_trees_vector.reserve(main_tokens_size);
		size_t count = 0;
		for (size_t i = 0; i < main_tokens_size; i++)
		{
			for (const auto& vec_tokens : copy_tokens)
			{
				if (vec_tokens[2] == main_tokens[i])
				{
					buff_tree.insert(std::make_pair(count, vec_tokens[2]));
					count++;
					buff_tree.insert(std::make_pair(count, vec_tokens[0]));
				}
			}
			buff_trees_vector.push_back(buff_tree);
			count = 0;
			buff_tree.clear();
		}
#ifdef MAKE_BUFF_TREES_FUNC_DEBUG
		fmt::print("Buffer tree\n");
		for (const auto& var : buff_trees_vector) {
			ranges::for_each(var, print_map);
			fmt::print("____________\n");
		}
		fmt::print("Buffer tree is end size of Buffer tree: {}\n", buff_trees_vector.size());
#endif // MAKE_BUFF_TREES_FUNC_DEBUG

		return (buff_trees_vector);
	}
}

int main(int argc, char** argv)
{
	auto var = make_buff_tree(test_copy_tokens);

	return (0);
}