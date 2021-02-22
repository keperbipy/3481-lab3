#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
void printInstruction(std::stringstream& x);
std::string getRegister(char);
std::string getAddress(std::stringstream&);
bool isData(std::stringstream&);
std::string getData(std::stringstream&);
using namespace std;

int main(int argc, char *argv[])
{
    char *file;
    std::stringstream ss;
    if (argc != 2) {
        std::cout << "Invalid Arguments!";
    }
    else {
        file = argv[1];
    }
    std::ifstream inf(file);
    if (!inf) {
        std::cerr << "Couldn't open file." << std::endl;
    }

    //Read line from file, send to printInstruction, then clear.
    while (inf) {
        std::string input;
        std::getline(inf, input);
        ss << input;
        printInstruction(ss);
        ss.str("");
    }
}


//Pulls the address information from each line.
std::string getAddress(std::stringstream& x) {
    std::string address;
    address = x.str();
    address = address.substr(0,6);
    return address;
}

//Checks if a specific line has data on it.
bool isData(std::stringstream& x) {
    std::string address;
    address = x.str();
    if (address.empty()) {
        return false;
    }
    address = address.substr(7, address.length());
    if (!address.find_first_not_of("01234567879abcde", 0)) return false;
    else return true;
}

//Pull the data instructions from each line.
std::string getData(std::stringstream& x) {
    std::string data;
    data = x.str();
    data = data.substr(7, data.length()); //Remove address from string.
    data = data.substr(0, data.find_first_of(" ")); //Cut off trailing spaces from string.
    return data;
}

void printInstruction(std::stringstream& x) {
    std::string address;
    address = getAddress(x);
    std::cout << address;
    std::string data;
    if (isData(x)) {
        data = getData(x);
        if (data.size() == 16) {
            std::cout << ".quad" << std::endl;
        }
		else if (data[0] == '0' && data[1] == '0') {
            std::cout << "halt" << std::endl;
        }
		else if (data[0] == '1' && data[1] == '0') {
            cout << "nop" << endl;
        }
        else if (data[0] == '2') {
            
             if(data[1] == '0'){
                cout << "rrmovq " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
             }
             else if (data[1] == '1') {
                cout << "cmovle " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
             }
             else if (data[1] == '2') {
                cout << "cmovl " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
             }
             else if (data[1] == '3') {
                cout << "cmove " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
             }
             else if (data[1] == '4') {
                cout << "cmovne " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
             }
             else if (data[1] == '5') {
                cout << "cmovge " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
             }
             else if (data[1] == '6') {
                cout << "cmovg " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
             }
                                                                                                                
        }                                                                                                     
        else if (data[0] == '3') {
            std::cout << "irmovq" << std::endl;
        }   
		else if (data[0] == '4') {
            std::cout << "rmmovq" << std::endl;
        }
		else if (data[0] == '5') {
            std::cout << "mrmovq" << std::endl;
        }
        else if (data[0] == '6') {
            
            if(data[1] == '0'){
                cout << "addq " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
            }
            else if (data[1] == '1') { 
                 cout << "subq " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
            }
            else if (data[1] == '2') {
                 cout << "andq " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
            }
            else if (data[1] == '3') {
                 cout << "xorq " << getRegister(data[2]) << ", " << getRegister(data[3]) << endl;
            } 
        }
		else  if (data[0] == '7') {
            std::cout << "jXX" << std::endl;
        }
        else  if (data[0] == '8') {
            std::cout << "call" << std::endl;
        }
        else if (data[0] == '9') {
            std::cout << "ret" << std::endl;
        }
		else if (data[0] == 'a' || data[0] == 'A') {
            cout << "pushq " << getRegister(data[2]) << endl;
        }
		else if (data[0] == 'b' || data[0] == 'B') {
            cout << "popq " << getRegister(data[2]) << endl;
        }
		
        else std::cout << std::endl;
    } 
    else std::cout << std::endl;
//    std::cout << data[0] << std::endl;

}

//Returns register name from given byte.
std::string getRegister(char reg) {
    if (reg == '0') {
        return "%rax";
    }
    else if (reg == '1') {
        return "%rcx";
    }
    else if (reg == '2') {
        return "%rdx";
    }
    else if (reg == '3') {
        return "%rbx";
    }
    else if (reg == '4') {
        return "%rsp";
    }
    else if (reg == '5') {
        return "%rbp";
    }
    else if (reg == '6') {
        return "%rsi";
    }
    else if (reg == '7') {
        return "%rdi";
    }
    else if (reg == '8') {
        return "%r8";
   }
   else if (reg == '9') {
        return "%r9";
   }
  else if (reg == 'a') {
        return "%r10";
  }
  else if (reg == 'b') {
        return "%r11";
  }
  else if (reg == 'c') {
        return "%r12";
  }
  else if (reg == 'd') {
        return "%r13";
  }
  else if (reg == 'e') {
        return "%r14";
  }
  else return "";
}
