#include "rocketinfo.h"
Rocket* getRocket(FILE* rocketFile){
	Rocket* rocket = malloc(sizeof(Rocket));
	
	/*wait for field lines*/
	char c;
	while((c=getc(rocketFile))!=':');

	fscanf(rocketFile, "%d", &(rocket->ncomponents));
	if(rocket->ncomponents > MAX_COMPONENTS){
		fprintf(stderr, "Err: (getRocket) too many components\n");
		return NULL;
	}

	int i;
	for (i=0;i<rocket->ncomponents;i++){

		/*wait for field lines*/
		while((c=getc(rocketFile))!=':');
		
		if(fscanf(rocketFile, "%lf %lf %lf %lf", &(rocket->m[i]),
				&(rocket->CM[i]), &(rocket->CN_alpha[i]),
				&(rocket->Z[i])) != 4){
			fprintf(stderr, "Err: (getRocket) malformed rocketFile\n");
			return NULL;
		}
	}

	return rocket;
}

void printRocket(const Rocket* rocket, FILE* rocketFile){
	if(rocket->ncomponents <= 0) return;

	fprintf(rocketFile, "ncomponents: %d\n\n", rocket->ncomponents);
	
	fprintf(rocketFile, "# m [g]\t CM [cm] CN []\t Z [cm]\n");
	int i;
	for(i=0; i<rocket->ncomponents; i++)
		fprintf(rocketFile, ": %.3f\t %.3f\t %.3f\t %.3f\n", rocket->m[i],
				rocket->CM[i], rocket->CN_alpha[i],
				rocket->Z[i]);
}

