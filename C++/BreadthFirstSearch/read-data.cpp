#include <iostream> 
#include <fstream>
#include <algorithm>
#include <vector>

std::vector<std::pair<int,int>> string_to_pairs(std::string str)
{
    // Store data
    std::vector<std::pair<int,int>> data; 
    // Find first comma 
    int first, second;
    int lbracket, comma, rbracket;
    lbracket = str.find("(");
    // While there is another bracket
    while(lbracket < str.size())
    {
	// Find indices of "(", ",", ")"
	comma = str.find(",", lbracket);
	rbracket = str.find(")", lbracket);
	// Read int from substring
	first = std::stoi(str.substr(lbracket+1,comma-1));
	second = std::stoi(str.substr(comma+1, rbracket-1));
	// Find next left bracket
	lbracket = str.find("(", lbracket+1);
	// Add pair to data
	data.push_back(std::make_pair(first, second));
    }
    return data;
}

int main()
{
    std::string line;
    std::vector<std::pair<int,int>> data; 
    std::ifstream myfile ("data_toy.txt");
    if (myfile.is_open())
    {
	while(getline(myfile, line)) 
	{
	    // ... Only one line
	}
	myfile.close();
    }
    string_to_pairs(line);
    data = string_to_pairs(line);
    
    // Print data
    for_each(data.begin(), data.end(), [](std::pair<int, int> p)
	    { std::cout << p.first << ", " << p.second << "\n"; });
    return 0;
}
