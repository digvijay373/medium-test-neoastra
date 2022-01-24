/* This program takes string input (until -1 is given as input)
   and checks whether the string is an URL by matching the patterns
   of an typical URL and then appends it to url.txt file if the 
   string is not an url then it appends it to names.txt file  */
#include <bits/stdc++.h>
#include<fstream>
using namespace std;
#define NO_OF_CHARS 256

int getNextState(string pat, int M, int state, int x)
{
	// If the character c is same as next character
	// in pattern,then simply increment state
	if (state < M && x == pat[state])
		return state+1;

	// ns stores the result which is next state
	int ns, i;

	for (ns = state; ns > 0; ns--)
	{
		if (pat[ns-1] == x)
		{
			for (i = 0; i < ns-1; i++)
				if (pat[i] != pat[state-ns+1+i])
					break;
			if (i == ns-1)
				return ns;
		}
	}

	return 0;
}

/* This function builds the TF table which represents the 
	Finite state machine for a given pattern */
void computeTF(string pat, int M, int TF[][NO_OF_CHARS])
{
	int state, x;
	for (state = 0; state <= M; ++state)
		for (x = 0; x < NO_OF_CHARS; ++x)
			TF[state][x] = getNextState(pat, M, state, x);
}

/* returns the first occurrences of pat in txt */
int search(string pat, string txt)
{
	int M = pat.size();
	int N = txt.size();

	int TF[M+1][NO_OF_CHARS];

	computeTF(pat, M, TF);
     int ans;
	// Process txt over FA.
	int i, state=0;
	 for (i = 0; i < N; i++)
	 {
		state = TF[state][txt[i]];
		if (state == M)
		{                //stores the first occurence of the pattern in txt
			ans=i-M+1;
			break;
		}  
	}
	return ans;
}

// Main function
int main()
{
   

	string txt ;
	fstream f1;
	fstream f2;
	getline(cin , txt);  
     while(txt!="-1"){
    
	string pat = "https://";
	string pat2="www.";
	string pat3=".com";
	int ans =search(pat, txt);
	int ans2= search(pat2 , txt);
	int ans3=search(pat3 , txt);
	
	if(ans==0 && ans2==8 && ans3>=13&&  ans3<=75)    // we are considering the max length of domain name to be 63
		{   f1.open("url.txt", ios::app);
	f1<<txt<<"\n";
	f1.close();
		cout<<"url"<<"\n";
	}
	else
	{
		 f2.open("name.txt", ios::app);
	f2<<txt<<"\n";
	f2.close();
		cout<<"Name"<<"\n";
	}

	getline(cin , txt);  

}
	return 0;
}




//Digvijay Singh

