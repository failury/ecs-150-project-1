# ecs 150 project 1

# Used online source

https://www.techiedelight.com/split-string-cpp-using-delimiter/

```c++
void tokenize(std::string const &str, const char* delim,
			std::vector<std::string> &out)
{
	char *token = strtok(const_cast<char*>(str.c_str()), delim);
	while (token != nullptr)
	{
		out.push_back(std::string(token));
		token = strtok(nullptr, delim);
	}
}
```

The code is used for split strings by a specific delim.