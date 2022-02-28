#include<bits/stdc++.h>
#include<fstream>
using namespace std;
 
int matrix[26][52];

// This function generates the key in a cyclic manner until
// it's length is not equal to the length of plainText
string generateKey(string plainText, string keyStream){
    int x = plainText.size();
 
    for (int i = 0; ; i++){
        if (x == i)
            i = 0;
        if (keyStream.size() == plainText.size())
            break;
        keyStream.push_back(keyStream[i]);
    }
    return keyStream;
}

// This function check valid or invalid input
bool isOnlyAlbhabet(string plainText, string keyStream){
    
    for(int i=0;i<plainText.size();i++){
        if(plainText[i] != ' ' && isalpha(plainText[i]) == false){
            return false;
        }
    }

    for(int i=0;i<keyStream.size();i++){
        if(keyStream[i] != ' ' && isalpha(keyStream[i]) == false){
            return false;
        }
    }
return true;

}

// Function to initialize matrix
void initialize_matrix(){
    int i, j;
 
    for (i = 0; i < 26; i++){
        for (j = 0; j < 26 - i; j++) {
            matrix[i][j] = j + i;
        }
 
        for (j = 26 - i; j < 26; j++) {
            matrix[i][j] = (j + i) - 26;
        }
 
        for (j = 26; j < 52 - i; j++) {
            matrix[i][j] = j + i - 26;
        }
 
        for (j = 52 - i; j < 52; j++) {
            matrix[i][j] = (j + i) - 52;
        }
    }
}

// This function do Encyption 
string encrypt(string plainText, string key){
   
    int size = plainText.length();
    string output = "";          
       
    for(int i=0; i<size; i++){
        char ch = plainText[i];
        if (isupper(ch)) {
            output.push_back(matrix[key[i] - 97][ch - 65] + 65);
        }
        else {
            output.push_back(matrix[key[i] - 97][ch - 97 + 26] + 97);
        }
    }
 
    return output;
}
 
 //This function to Decryption
string decrypt(string cipher_text, string key){
    
    
    string output = "";
 
    int size = cipher_text.length();
    
   for(int count = 0; count < size; count++){
        char ch = cipher_text[count];
        if (isupper(ch))
        {
            for (int i = 0; i < 26; i++)
            {
                if (matrix[key[count] - 97][i] == ch - 65) {
                    output.push_back(i + 65);
                }
            }
        }
        else {
            for (int i = 26; i < 52; i++){
                if (matrix[key[count] - 97][i] == ch - 97) {
                    output.push_back(i + 97 - 26);
                }
            }
        }
        
    }
    return output;
}
 
int main(){
    string plainText;
    string keyStream;

    cout<<"Enter PlainText : ";
    getline(cin, plainText);

    cout<<"Enter KeyStream : ";
    getline(cin, keyStream);

    // vector to store position of space(" ")
    vector<int>position;

    for(int i=0;i<plainText.size();i++){
        if(plainText[i] == ' '){
            position.push_back(i);
        }
    }

    string plaintext = "";
    stringstream ss(plainText);
    string word;
    while(ss>>word){
        plaintext += word;
    }


    cout<<"\n";

    int n = keyStream.length();
 
    for (int j = 0; j < n; j++) {
        keyStream[j] = tolower(keyStream[j]);
    }

    initialize_matrix();

    ofstream file;
    file.open("191IT142_IT352_P4_Output_TC6.txt");

   if(isOnlyAlbhabet(plaintext, keyStream) == false){
       cout<<"Error : Input contain non-alphabet character"<<"\n";
       file<<"Error : Input contain non-alphabet character"<<"\n";

   }
    else {
        
        string cipher_text;
        string original_text;
    
        string key = generateKey(plaintext, keyStream);
        cipher_text = encrypt(plaintext, key);
        original_text = decrypt(cipher_text, key);

       for(int i=0;i<position.size();i++){
           cipher_text.insert(position[i]," ");
           original_text.insert(position[i]," ");

       } 
    
    cout<<"After Encryption :"<<'\n';
    cout<<"PlainText : "<<plainText<<"\n";
    cout<<"CipherText : "<< cipher_text << "\n";
    cout<<"KeyStream : "<< keyStream << "\n\n";

    cout<<"After Decryption :"<<"\n";cout<<"CipherText : "<<cipher_text<<"\n";
    cout <<"PlainText : "<<original_text<<"\n";
    cout<<"KeyStream : "<<keyStream<<"\n\n";

    file<<"After Encryption :"<<'\n';
    file<<"PlainText : "<<plainText<<"\n";
    file<<"CipherText : "<< cipher_text << "\n";
    file<<"KeyStream : "<< keyStream << "\n\n";

    file<<"After Decryption :"<<"\n";
    file<<"CipherText : "<<cipher_text<<"\n";
    file <<"PlainText : "<<original_text<<"\n";
    file<<"KeyStream : "<<keyStream<<"\n\n";

    
 }
   file.close();

    return 0;
}