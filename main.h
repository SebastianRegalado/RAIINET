#ifndef MAIN_H
#define MAIN_H

#include <map>
#include <string>

void error_message() {
    throw "Please enter correct arguments, inorder to proceed with gameplay.\n";
}

bool is_valid_abilities(string order) {
    int count=0;

    std::map<char, int> valid_ability { // Dictionary of Valid Inputs and Occurence of Abilities
        {'L',2},
        {'F',2},
        {'D',2},
        {'S',2},
        {'P',2},
        {'M',2},
        {'E',2},
        {'I',2}
    };

    for(int i=0; i<(int)order.length(); ++i) { // Check the player's input order
        if (valid_ability.count(order[i])==0) { // Ability is not defined
            return false;
        }
        
        if (valid_ability[order[i]]<=0) { // Too Many Occurences of Ability
            return false;
        } else {
            ++count;
            valid_ability[order[i]] -= 1; // Decrement Number of Abilities Remaining
        }
    }

    return (count==5) ? true : false;
}

bool is_valid_link(string order) {
    int v_count = 0; 
    int d_count = 0;

    int v[5] = {0};
    int d[5] = {0};

    for(int i=0; i<(int)order.length(); ++i) {
        if ((i%2)==0) { // All Even-Index Elements should be Data Link Type
            if (order[i]=='V') { // Increment Virus Count
                ++v_count;
            } else if (order[i]=='D') { // Increment Data Count
                ++d_count;
            } else { // Not Valid link Type
                return false;
            }

            if (v_count>4) return false; // False if Too Many Virus Count
            if (d_count>4) return false; // False if Too Many Data Count
        } else {
            if ((order[i]<'0')||(order[i]>'4')) return false; // Not a Valid Link Number
            
            if (order[i-1]=='V') { // Check Valid Virus Link Number Occurence
                if (v[order[i]-'0']!=0) { // Check if Virus Link Number is Already Defined
                    return false; 
                } else { // Define and Increment Virus Link Number Occurence
                    ++v[order[i]-'0'];
                }
            }
            
            if (order[i-1]=='D') { // Check Valid Data Link Number Occurence
                if (d[order[i]-'0']!=0) { // Check if Data Link Number is Already Defined
                    return false;
                } else {
                    ++d[order[i]-'0']; // Define and Increment Virus Link Number Occurence
                }
            }
        }
    }

    return ((v_count==4)&&(d_count==4)) ? true : false;
}

void setup(int argc, char * argv[], string &ab1_info, string &ab2_info, 
        string &l1_info, string &l2_info, bool &graphics) {

    bool ab1_init = false;
    bool ab2_init = false;
    bool l1_init = false;
    bool l2_init = false;
    bool g_init = false;
    string prev_command;

    for(int i=1; i<argc; ++i) {
        const char* temp_1 = argv[i];
        string temp_arg_1(temp_1);

        if (temp_arg_1=="-ability1") {
            if (ab1_init) { // check if ability already initialized -- terminate
                error_message();
            }

            if (!((i+1)<argc)) {
                ab1_init = true;
            } else {
                ++i;

                if (is_valid_abilities(argv[i])) { // check if abilities are valid
                    ab1_info = argv[i];
                    ab1_init = true;
                } else if (argv[i][0]=='-') { // check if arg is a command
                    ab1_init = true;
                    --i;
                } else { // return error message and terminate program
                    error_message();
                }
            }

        } else if (temp_arg_1=="-ability2") {
            if (ab2_init) { // check if ability already initialized -- terminate
                error_message();
            }

            if (!((i+1)<argc)) {
                ab2_init = true;
            } else {
                ++i;

                if (is_valid_abilities(argv[i])) { // check if abilities are valid
                    ab2_info = argv[i];
                    ab2_init = true;
                } else if (argv[i][0]=='-') { // check if arg is a command
                    ab2_init = true;
                    --i;
                } else { // return error message and terminate program
                    error_message();
                }
            }

        } else if (temp_arg_1=="-link1") {
            if (l1_init) { // check if link already initailized -- terminate
                error_message();
            }

            if (!((i+1)<argc)) {
                l1_init = true;
            } else {
                ++i;

                if (is_valid_link(argv[i])) { // check if links are valid
                    l1_info = argv[i];
                    l1_init = true;
                } else if (argv[i][0]=='-') { // check if arg is a command
                    l1_init = true;
                    --i;
                } else { // return error message and terminate program
                    error_message();
                }
            }
        } else if (temp_arg_1=="-link2") {
            if (l2_init) { // check if link already initailized
                error_message();
            }

            if (!((i+1)<argc)) {
                l2_init = true;
            } else {
                ++i; 
            
                if (is_valid_link(argv[i])) { // check if links
                    l2_info = argv[i];
                    l2_init = true;
                } else if (argv[i][0]=='-') { // check if arg is a command
                    l2_init = true;
                    --i;
                } else { // return error message and terminate program
                    error_message();
                }
            }
        } else if (temp_arg_1=="-graphics") {
            if (g_init) {
                error_message();
            } else {
                graphics = true;
                g_init = true;
            }
        } else {
            error_message();
        }
    }
}

#endif
