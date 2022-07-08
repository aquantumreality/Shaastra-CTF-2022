#include<bits/stdc++.h>
using namespace std;

#define N 100

int blueRotor[N]  = {0, 10, 4, 26, 21, 6, 1, 14, 7, 24, 5, 15, 25, 3, 17, 12, 18, 11, 22, 23, 16, 8, 19, 13, 9, 2, 20};
int redRotor[N]   = {0, 20, 4, 7, 24, 1, 12, 26, 6, 14, 2, 17, 21, 9, 5, 22, 8, 15, 25, 16, 13, 11, 3, 10, 18, 23, 19};
int greenRotor[N] = {0, 2, 11, 16, 12, 26, 19, 3, 13, 6, 20, 8, 5, 22, 17, 1, 15, 21, 7, 24, 4, 14, 9, 23, 18, 10, 25};
int reflector[N]  = {0, 4, 16, 11, 1, 21, 13, 19, 24, 14, 12, 3, 10, 6, 9, 23, 2, 26, 25, 7, 22, 5, 20, 15, 8, 18, 17};

int rotor1arr[N], rotor1barr[N];
int rotor2arr[N], rotor2barr[N];
int rotor3arr[N], rotor3barr[N];

/*pointers to make maniplating above arrays easier*/
int* rotor1 = rotor1arr; /*left to right maps*/
int* rotor1b = rotor1barr; /*right to left maps*/
int* rotor2 = rotor2arr;
int* rotor2b = rotor2barr;
int* rotor3 = rotor3arr;
int* rotor3b = rotor3barr;

int* rotateD(int* a, int num_steps){
	int b[N];
	int i=1;
	for(i=1; i<=num_steps; i++){
		b[i] = a[26-num_steps+i];
	}
	for(; i<=26; i++){
		b[i] = a[i-num_steps];
	}
	for(i=1; i<=26; i++){
		if(b[i] + num_steps -26 >= 1)
			b[i] = b[i] + num_steps - 26;
		else b[i] = b[i] + num_steps;
	}
	for(i=1; i<=26; i++)
		a[i] = b[i];
	return a;
}

int* rotateU(int* a, int num_steps){
	int b[N];
	int i=1;
	for(i=1; i<=26-num_steps; i++){
		b[i] = a[num_steps+i];
	}
	for(; i<=26; i++){
		b[i] = a[i-26+num_steps];
	}
	for(i=1; i<=26; i++){
		if(b[i] - num_steps > 0)
			b[i] = b[i] - num_steps;
		else
			b[i] = b[i] - num_steps + 26;
	}
	for(i=1; i<=26; i++)
		a[i] = b[i];
	return a;
}

void printarr(int* rotor){
	for(int i=1; i<=26; i++){
		cout << *(rotor + i) << ' ';
	}
}

void encode(char key1, char key2, char key3, string plaintext){ /*key letters to be entered in capital*/
	string codetext;
	int foo;
	
	/*Configure rotors so that key letters appear at rotori[1]*/
	rotor1 = rotateU(rotor1, ((int) key1) - 64 - 1);
	rotor2 = rotateU(rotor2, ((int) key2) - 64 - 1);
	rotor3 = rotateU(rotor3, ((int) key3) - 64 - 1);
	
	rotor1b = rotateU(rotor1b, ((int) key1) - 64 - 1);
	rotor2b = rotateU(rotor2b, ((int) key2) - 64 - 1);
	rotor3b = rotateU(rotor3b, ((int) key3) - 64 - 1);
	
	for(int i=0; i<plaintext.length(); i++){
	/*debugging. ignore all this	
		cout << i <<"\trotor 1: "; printarr(rotor1); cout << endl;
		cout<<"\trotor 1b: "; printarr(rotor1b); cout << endl;
		cout<<"\trotor 2: "; printarr(rotor2); cout << endl;
		cout<<"\trotor 2b: "; printarr(rotor2b); cout << endl;
		cout<<"\trotor 3: "; printarr(rotor3); cout << endl;
		cout<<"\trotor 3b: "; printarr(rotor3b); cout << endl;
		
		cout<<"\nrotor1 maps "<<plaintext[i]<<" to "<<rotor1[(int)plaintext[i]-64]<<endl;
		cout<<"rotor2 maps "<<rotor1[(int)plaintext[i]-64]<<" to "<<rotor2[rotor1[(int)plaintext[i]-64]]<<endl;
		cout<<"rotor3 maps this to "<<rotor3[rotor2[rotor1[(int)plaintext[i]-64]]]<<endl;
		cout<<"reflector maps this to "<<reflector[rotor3[rotor2[rotor1[(int)plaintext[i]-64]]]]<<endl;
		cout<<"rotor3b maps this to "<<rotor3b[reflector[rotor3[rotor2[rotor1[(int)plaintext[i]-64]]]]]<<endl;
		cout<<"rotor2b maps this to "<<rotor2b[rotor3b[reflector[rotor3[rotor2[rotor1[(int)plaintext[i]-64]]]]]]<<endl;
		cout<<"rotor1b maps this to "<<rotor1b[rotor2b[rotor3b[reflector[rotor3[rotor2[rotor1[(int)plaintext[i]-64]]]]]]]<<endl;
	*/	
		foo = 64 + rotor1b[rotor2b[rotor3b[reflector[rotor3[rotor2[rotor1[(int)plaintext[i]-64]]]]]]];
	//	codetext[i] = (char) foo;
		if(isalpha(plaintext[i]))
			cout<< (char) foo;
		else
			cout<<plaintext[i];
		
		rotateU(rotor1, 1);
		rotateU(rotor1b, 1);
		
		if((i+1)%26 == 0){
			rotateU(rotor2, 1);
			rotateU(rotor2b, 1);
		}
		if((i+1)%(26*26) == 0){
			rotateU(rotor3, 1);
			rotateU(rotor3b, 1);
		}
	}
	
//	return codetext;
}


int main(){
	/*initialising rotors*/
	for(int i=1; i<=26; i++){
		rotor1arr[i] = redRotor[i];
		rotor2arr[i] = greenRotor[i];
		rotor3arr[i] = blueRotor[i];
		
		rotor1barr[rotor1[i]] = i;
		rotor2barr[rotor2[i]] = i;
		rotor3barr[rotor3[i]] = i;
	}
	string pt;
	getline(cin, pt);
	encode('G', 'S', 'N', pt);
	//cout << ct;
}
