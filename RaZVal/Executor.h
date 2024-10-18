#include<unordered_map>
#include"types.h"
#include<string>
#include<memory>
class VariableSpace {
private:
    std::unordered_map<std::string, std::unique_ptr<Object>> variables;
public:
    void assign(std::string name, std::unique_ptr<Object> value) {
        variables[name] = std::move(value);
    }
    
    void destroy(std::string name) {
        variables.erase(variables.find(name));
    }
};

namespace parser {

}
