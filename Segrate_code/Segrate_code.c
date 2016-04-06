# include <stdlib.h>

int n;
char buffer[100];
char vocali[]="aeiouy";
char vocaliCambiate[]="eiouya";
char consonanti[]="bcdfghjklmnpqrstvwxz";
char consonantiCambiate[]="cdfghjklmnpqrstvwxzb";

int vocali(char c) {
    return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='y');
}

char traduciVocali(char c) {
	int i;
	for (i=0; i<n; i++)
		if (c==vocali[i]) return vocaliCambiate;
}

char TraduciConsonanti(char c){
	int i;
	for (i=0; i<20; i++)
		if (c==consonanti[i]) return consonantiCambiate[i];
}

int main()
{
	FILE *in, *out;
	int i,j;
	in=fopen("input.txt","r");
	out=fopen("output.txt","w");

	fscanf(in,"%d",&N);
	fgets(buffer,81,in);

	for (i=0; i<N; i++)
	{
		fgets(buffer,81,in);
		for (j=0; buffer[i]!='\0'; i++)
		{
			int flag=0;
			char temp, c=tlower(buffer[i]);
			if (c!=buffer[i]) flag=1;
			if (isalpha(c))
			{
				if (vocale(c)) temp=traduciVocali(c);
				else           temp=TraduciConsonanti(c);

				if (flag) temp=toupper(temp);

			}
		}
	}

}