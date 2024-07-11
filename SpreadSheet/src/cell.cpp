#include <../headers/cell.h>

Cell::Cell():val("_"){}

Cell::Cell(const Cell &rhv):val(rhv.val){}

Cell::Cell(int val):val(std::to_string(val)){}

Cell::Cell(Cell &&rhv):val(std::move(rhv.val)){}

Cell::Cell(double val):val(std::to_string(val)){}

Cell::Cell(char val){
    this->val = val;
}

Cell::Cell(bool val){
    if(val){
        this->val = "true";
    }else{
        this->val = "false";
    }
}

Cell::Cell(std::string val):val(val){}

Cell::Cell(const std::vector<int> &val){
    for(int i = 0; i < val.size(); i++){
        this->val += (std::to_string(val[i]) + ",");
    }
    this->val.pop_back();
}

const Cell &Cell::operator=(const Cell &rhv){
    if(&rhv == this){
        return *this;
    }

    val = rhv.val;
    return *this;
}

const Cell &Cell::operator=(Cell &&rhv){

    val = std::move(rhv.val);
    return *this;
}

const Cell &Cell::operator=(int rhv){

    val = std::to_string(rhv);
    return *this;
}

const Cell &Cell::operator=(double rhv){
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << rhv;
    val = stream.str();
    return *this;
}

const Cell &Cell::operator=(char rhv){

    val = rhv;
    return *this;
}

const Cell &Cell::operator=(bool rhv){

    if(rhv){
        val = "true";
    }else{
        val = "false";
    }
    return *this;
}

const Cell &Cell::operator=(std::string rhv){

    val = rhv;
    return *this;
}

const Cell &Cell::operator=(const std::vector<int> &rhv){

    val = "";

    for(auto it = rhv.begin(); it != rhv.end(); it++){
        val += (std::to_string(*it) + ",");
    }
    val.pop_back();

    return *this;
}

Cell::operator int(){
    try{
        return std::stoi(val);
    }catch(const std::invalid_argument& e){
        throw std::invalid_argument("can't convert to int");
    }
}

Cell::operator double(){
    try{
        return std::stod(val);
    }catch(const std::invalid_argument& e){
        throw std::invalid_argument("can't convert to double");
    }
}

Cell::operator char(){
    return val[0];
}

Cell::operator bool(){
    if(val == "true"){
        return true;
    }else if(val == "false"){
        return false;
    }else{
        throw std::invalid_argument("cant convert to bool");
    }
}

Cell::operator std::string(){
    return val;
}

Cell::operator std::vector<int>(){
     if (val == ""){
        throw std::logic_error("Cell is empty");
    }
    std::vector<int> tmp;
    std::string forTemp = "";
    for(int i = 0; i<val.size();i++){
        if (std::isdigit(val[i])){
            forTemp += val[i];
        }else if(val[i] == ','){
            if (i == 0){
                throw std::invalid_argument("cant convert to vectorll");
            }
            tmp.push_back(std::stoi(forTemp));
            forTemp = "";
        }else{
            std::cout<<val[i]<<std::endl;
            throw std::invalid_argument("cant convert to vectorjhhhh");
        }
    }
    if (forTemp.size() != 0){
        tmp.push_back(std::stoi(forTemp));
    }
    return tmp;
}

bool operator==(const Cell &lhv, const Cell &rhv){
    return lhv.val == rhv.val;
}

bool operator!=(const Cell &lhv, const Cell &rhv){
    return lhv.val != rhv.val;
}

std::ostream& operator<<(std::ostream& out, const Cell& ob){
    out<<ob.val;
    return out;
}

std::istream& operator>>(std::istream& in,Cell& ob){
    in>>(ob.val);
    return in;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob) {
    out << "[";
    for (int i = 0; i<ob.size(); i++){
        out << ob[i];
        if (i != ob.size() - 1){
            out << ", ";
        }
    }
    out << "]";
    return out;
}



const Cell &Cell::operator=(const char * rhv){
    val = std::string(rhv);
    return *this;
}