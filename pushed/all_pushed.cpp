#include <bits/stdc++.h>

using namespace std;

int main(){

	int rep;
	char var[20];
	cin >> rep;				//  Qtd de vezes que vai rodar o loop.
	for(int hue = 0; hue < rep; hue++){
		cout << "File1" << endl;
		scanf("%s", var);

		string aux1(var);
		aux1 = "IC(90)_" + aux1;
		const char* f3 = aux1.c_str();

		int a, b, c;
		FILE *fp = fopen(var, "r");
		FILE* fp3 = fopen(f3, "w+");

		fscanf(fp, "%d %d %d", &a, &b, &c);
		fprintf(stdout, "%d %d %d\n", a, b, c);
	
		int n1[a];
		for(int i = 1; i <= a; i++){
			fprintf(fp3, "%s%d = c(", var, i);
			for(int j = 0; j < b; j++){
				for(int k = 0; k < c; k++){
					fscanf(fp, "%d", &n1[k]);
					fprintf(fp3, "%d", n1[k]);
					if((j + 1) == b){
						if( (k+1) == c );					
						else{
							fprintf(fp3, ",");
							fprintf(fp3, " ");
						}				
					}
					else{
						fprintf(fp3, ",");
						fprintf(fp3, " ");
					}
				}
			}
			fprintf(fp3,"%s%d_mean = mean(%s%d)\n", var, i, var, i);
			fprintf(fp3,"%s%d_sd = sd(%s%d)\n", var, i, var, i);
			fprintf(fp3, "%s%dL90 = %s%d_mean - qnorm(0.95) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR90 = %s%d_mean + qnorm(0.95) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dL95 = %s%d_mean - qnorm(0.975) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR95 = %s%d_mean + qnorm(0.975) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dL97_5 = %s%d_mean - qnorm(0.9875) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR97_5 = %s%d_mean + qnorm(0.9875) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dL98_75 = %s%d_mean - qnorm(0.99375) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR98_75 = %s%d_mean + qnorm(0.99375) * %s%d_sd\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%d_mean\n", var,i);
			fprintf(fp3, "%s%dL90\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR90\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dL95\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR95\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dL97_5\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR97_5\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dL98_75\n", var, i, var, i, var, i);
			fprintf(fp3, "%s%dR98_75\n\n\n", var, i, var, i, var, i);
		}
		fclose(fp);
		fclose(fp3);
		cout << "Output file : " << endl;
		cout << f3 << endl;
	}
	return 0;
}