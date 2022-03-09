#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// Take the ASCII value of the entered input then covert them into binary form
string to_binary(string key){
    
    string bin = "";
    for (int i = 0; i < key.length(); i++) {
        string binary = bitset<8>(key[i]).to_string();
        bin += binary;
    }
    return bin;
}


// Array to hold the 16 keys
string round_keys[16];

// Function to do a circular left shift by 1
string shift_left_once(string key_chunk){ 

    string shifted="";  
        for(int i = 1; i < 28; i++){ 
            shifted += key_chunk[i]; 
        } 
        shifted += key_chunk[0];   
    return shifted; 
} 

// Function to do a circular left shift by 2
string shift_left_twice(string key_chunk){ 

    string shifted=""; 
    for(int i = 0; i < 2; i++){ 
        for(int j = 1; j < 28; j++){ 
            shifted += key_chunk[j]; 
        } 
        shifted += key_chunk[0]; 
        key_chunk= shifted; 
        shifted =""; 
    } 
    return key_chunk; 
}

void generate_keys(string key){
	// The Permutation Choice-1 table 
	int pc1[56] = { 57,49,41,33,25,17,9, 1,58,50,42,34,26,18, 10,2,59,51,43,35,27, 19,11,3,60,52,44,36,		 
	                63,55,47,39,31,23,15, 7,62,54,46,38,30,22, 14,6,61,53,45,37,29, 21,13,5,28,20,12,4 };
	
	// The Permutation Choice-2 table
	int pc2[48] = { 14,17,11,24,1,5, 3,28,15,6,21,10, 23,19,12,4,26,8, 16,7,27,20,13,2, 41,52,31,37,47,55, 
	30,40,51,45,33,48, 44,49,39,56,34,53, 46,42,50,36,29,32 
	}; 


	// Compressing the key using the PC1 table
	string perm_key =""; 
	for(int i = 0; i < 56; i++){ 
		perm_key += key[pc1[i]-1]; 
	} 
  
    ofstream file;
	file.open("191IT142_IT352_P5_Output_TC6.txt", ios::app);
	cout<<"Output of the Permutation Choice-I Operation : "<<perm_key<<"\n";
	file<<"Output of the Permutation Choice-I Operation : "<<perm_key<<"\n";

	
	// Dividing the result into two equal halves
	string left = perm_key.substr(0, 28); 
	string right = perm_key.substr(28, 28); 

	// Generating 16 keys
	for(int i=0; i<16; i++){ 
		// For rounds 1, 2, 9, 16 the key_chunks are shifted by one.
		if(i == 0 || i == 1 || i==8 || i==15 ){
			left = shift_left_once(left); 
			right = shift_left_once(right);
		} 
		// For other rounds, the key_chunks are shifted by two
		else{
			left = shift_left_twice(left); 
			right = shift_left_twice(right);
		}

	// The chunks are combined
	string combined_key = left + right;
	string round_key = ""; 

	// Finally, the PC2 table is used to transpose the key bits
	for(int i = 0; i < 48; i++){ 
		round_key += combined_key[pc2[i]-1]; 
	}   
	round_keys[i] = round_key;
		cout<<"Round Key "<<i+1<<" : "<<round_keys[i]<<"\n";
		file<<"Round Key "<<i+1<<" : "<<round_keys[i]<<"\n"; 
	} 

	file.close();

}
int main(){  
	string key;
	cout<<"\nEnter the key value : ";
	getline(cin, key);

	
    string binaryKey = to_binary(key);
    string temp = "0000000000000000000000000000000000000000000000000000000000000000";
	binaryKey = binaryKey + temp;
	
	
    ofstream file;
	file.open("191IT142_IT352_P5_Output_TC6.txt", ios::out);

	cout<<"First 56 bits as key value : "<<binaryKey.substr(0,56)<<"\n";
	file<<"First 56 bits as key value : "<<binaryKey<<"\n";
	
	file.close();
  	generate_keys(binaryKey);
	
	return 0;
} 
