#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int i = 0, j = 0, k = 0;

// Function to calculate GCD
int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int minv(int a, int m){
    a = a % m;
    for(int x=-m; x<m; x++){
        if((a*x)%m == 1) return x;
    }
    return 0;
}

void cofactor(vector<vector<int>> &v, vector<vector<int>> &t, int p, int q, int n){
    int i = 0, j = 0;

    for(int r=0;r<n;r++){
        for(int c=0;c<n;c++){
            if(r != p && c != q){
                t[i][j++] = v[r][c];
                if(j == n-1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinantOfMatrix(vector<vector<int>> &v, int n, int N){
    int d = 0;
    if(n == 1) return v[0][0];

    vector<vector<int>> temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){
        cofactor(v, temp, 0, f, n);
        d += sign * v[0][f] * determinantOfMatrix(temp, n - 1, N);
        sign = -sign;
    }
    return d;
}

void adjoint(vector<vector<int> > &v,vector<vector<int>> &adj,int n){
    if(n == 1){
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    vector<vector<int> >temp(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cofactor(v, temp, i, j, n);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinantOfMatrix(temp, n-1 , n));
        }
    }
}

bool keyInverse(vector<vector<int>> &v, vector<vector<int>> &keyInv, int n){
    int d = determinantOfMatrix(v, n, n);

    if(d == 0 || gcd(d,256) != 1) return false;

    int invDet = minv(d,256);

    vector<vector<int> > adj(n, vector<int>(n));
    adjoint(v, adj, n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            keyInv[i][j] = (adj[i][j]*invDet)%256;
    return true;
}

vector<vector<int>>encrypt(vector<vector<int>> &block, vector<vector<int>> &key, int n){
    vector<vector<int>>mul(n,vector<int>(n));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            mul[i][j]=0;
            for(k=0;k<n;k++)
            {
                mul[i][j]+=(block[i][k]%256*key[k][j]%256)%256;
                mul[i][j]%=256;
            }
        }
    }

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            mul[i][j]%=256;
        }
    }

    return mul;
}


int main(){
    string plainText;
    int n, m;
    cout<<"Enter PlainText : ";
    getline(cin, plainText);

    cout<<"Enter dimensions of key matrix : ";
    cin>>n;

    m = n;

    vector<vector<int>>IV(n,vector<int>(m));
    vector<vector<int>>key(n,vector<int>(m));
    vector<vector<int>>keyInv(n,vector<int>(m));

    cout<<"Enter the elements of n * n key matrix : "<<"\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>key[i][j];
        }
    }

    cout<<"Enter the elements of n * n IV matrix : "<<endl;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>IV[i][j];
        }
    }

    // Applying padding if block size not divisible by m
    while(plainText.length()%(m*n) != 0)
        plainText += (char)(0);

    //diving into blocks of size n * m size
    vector<vector<vector<int>>>blocks, encryption, decryption;

    for(int i=0;i<plainText.size();i+=(n*m)){
        vector<vector<int>>temp(n,vector<int>(n,0));
        int c = i;

        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
                if(c >= plainText.size())
                    break;
                else
                    temp[j][k] = plainText[c++];
        blocks.push_back(temp);
    }

    ofstream file;
    file.open("191IT142_IT352_P6_Output_TC6.txt", ios::out);


    cout<<"Blocks : "<<endl;
    file<<"Blocks : "<<endl;
    for(int i=0;i<blocks.size();i++){
        cout<<"Block "<<i<<" : "<<endl;
        file<<"Block "<<i<<" : "<<endl;
        for(int j=0;j<n;j++) {
            for (int k = 0; k < n; k++) {
                cout << (char) blocks[i][j][k] << " ";
                file << (char) blocks[i][j][k] << " ";
            }
            cout<<endl;
            file<<endl;

        }

    }

    bool res = keyInverse(key,keyInv,n);
    if(res) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (keyInv[i][j] < 0) keyInv[i][j] += 256;
            }
        }

        // CBC Encryption process

        for (int i = 0; i < blocks.size(); i++) {
            vector<vector<int>> next(n, vector<int>(m));
            if (i == 0) {

                for (int i1 = 0; i1 < n; i1++) {
                    for (int j = 0; j < m; j++) {
                        next[i1][j] = blocks[i][i1][j] ^ IV[i1][j];
                    }
                }
            } else {
                for (int i1 = 0; i1 < n; i1++) {
                    for (int j = 0; j < m; j++) {
                        next[i1][j] = blocks[i][i1][j] ^ blocks[i - 1][i1][j];
                    }
                }
            }

            encryption.push_back(encrypt(next, key, n));
        }

        cout<<"After Encryption : "<<"\n";
        file<<"After Encryption : "<<"\n";

        for (int i = 0; i < blocks.size(); i++) {
            cout<<"PlainText block and Encrypted block (ASCII values) : "<<i<<endl;
            file<<"PlainText block and Encrypted block (ASCII values) : "<<i<<endl;

            for(int j=0;j<n;j++) {
                for (int k = 0; k < n; k++) {
                    cout << (char) blocks[i][j][k] << " ";
                    file << (char) blocks[i][j][k] << " ";
                }
                cout<<"\n";
                file<<"\n";

            }


            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    int ch = encryption[i][j][k];
                    cout << ch << " ";
                    file << ch << " ";

                }
                cout<<"\n";
                file<<"\n";
            }



        }


        // CBC Decryption Process :

        vector<vector<int>> curr;
        curr = blocks[0];

        for (int i = 0; i < blocks.size(); i++) {
            vector<vector<int>> next(n, vector<int>(m));
            vector<vector<int>> temp = encrypt(encryption[i], keyInv, n);
            if (i == 0) {

                for (int i1 = 0; i1 < n; i1++) {
                    for (int j = 0; j < m; j++) {
                        next[i1][j] = temp[i1][j] ^ IV[i1][j];
                    }
                }
            } else {
                for (int i1 = 0; i1 < n; i1++) {
                    for (int j = 0; j < m; j++) {
                        next[i1][j] = temp[i1][j] ^ curr[i1][j];
                    }
                }
            }

            curr = next;
            decryption.push_back(next);
        }


        cout<<"After Decryption : " << "\n";
        file<<"After Decryption : " << "\n";
        for (int i = 0; i < blocks.size(); i++) {
            cout<<"Encrypted block (ASCII values) and Decrypted block " <<i<< " : "<<"\n";
            file<<"Encrypted block (ASCII values) and Decrypted block " <<i<< " : "<<"\n";

            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    int ch = encryption[i][j][k];
                    cout << ch << " ";
                    file << ch << " ";

                }
                cout<<"\n";
                file<<"\n";
            }


            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    cout << (char) decryption[i][j][k] << " ";
                    file << (char) decryption[i][j][k] << " ";
                }
                cout<<"\n";
                file<<"\n";
            }



        }
    }else{
        cout<<"Key-inverse does not exist"<<"\n";
        file<<"Key-inverse does not exist"<<"\n";
    }

    file.close();

    return 0;
}