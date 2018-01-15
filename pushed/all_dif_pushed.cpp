#include <bits/stdc++.h>

using namespace std;

int main(){

	int rep;
	char f1[20], f2[20];
	cin >> rep;				//  Qtd de vezes que vai rodar o loop.
	for(int hue = 0; hue < rep; hue++){
		cout << "File1" << endl;
		scanf("%s", f1);
		cout << "File2" << endl;
		scanf("%s", f2);

		string aux1(f1);
		string aux2(f2);
		string aux3 = aux1 + "_" + aux2;
		const char * var = aux3.c_str();
		aux1 = "DIF_" + aux1 + "<>" + aux2;
		const char* f3 = aux1.c_str();

		int a, b, c, a1, b1, c1;
		FILE *fp = fopen(f1, "r");
		FILE *fp2 = fopen(f2, "r");
		FILE* fp3 = fopen(f3, "w+");

		fscanf(fp, "%d %d %d", &a, &b, &c);
		fprintf(stdout, "%d %d %d\n", a, b, c);

		fscanf(fp2, "%d %d %d", &a1, &b1, &c1);
		fprintf(stdout, "%d %d %d\n", a1, b1, c1);
	
		if( (a == a1) and (b == b1) and (c == c1));
		else	throw "Comparacao nao pareada.";

		int n1[a], n2[a1];
		char t;
		for(int i = 0; i < a; i++){
			fprintf(fp3, "%s%d = c(", var, i);
			for(int j = 0; j < b; j++){
				for(int k = 0; k < c; k++){
					fscanf(fp, "%d", &n1[k]);
					fscanf(fp2, "%d", &n2[k]);
					printf("%d - %d\n", n1[k], n2[k]);
					fprintf(fp3, "%d", (n1[k] - n2[k]));
					if((j + 1) == b){
						if( (k+1) == c );					
						else{
							fscanf(fp, "%c", &t);
							fscanf(fp2, "%c", &t);
							fprintf(fp3, ",");
							fprintf(fp3, " ");
						}				
					}
					else{
						fscanf(fp, "%c",&t);
						fscanf(fp2, "%c", &t);
						fprintf(fp3, ",");
						fprintf(fp3, " ");
					}
				}
			}
			fprintf(fp3, ")\n");
			fprintf(fp3,"%s%d_mean = mean(%s%d)\n", var, i, var, i);
			fprintf(fp3,"%s%d_sd = sd(%s%d)\n", var, i, var, i);
			fprintf(fp3,"\t%s%d_zezao = (%s%d_mean/ %s%d_sd)\n",var, i, var, i, var, i );
			fprintf(fp3, "if(%s%d_mean < 0)\n", var, i);
			fprintf(fp3, "\t%s%d_zezao = %s%d_zezao * (-1)\n", var, i, var, i);
			fprintf(fp3,"%s%d_zezao\n",var, i);
			fprintf(fp3, "%s%dL90 = %s%d_mean - qnorm(0.95) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR90 = %s%d_mean + qnorm(0.95) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%d_mean\n", var,i);
			fprintf(fp3, "%s%dL90\n", var, i);
			fprintf(fp3, "%s%dR90\n\n", var, i);
			
		}
		fclose(fp);
		fclose(fp2);
		fclose(fp3);
		cout << "Output file : " << endl;
		cout << f3 << endl;
	}
	return 0;
}