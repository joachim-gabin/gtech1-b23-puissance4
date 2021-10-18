void grille(){


	for(int n=0;n<NUM_COLUMNS;n++){
		printf("--");
	}

	for(int z=0;z<NUM_ROWS;z++){
		for(int u=0;u<NUM_COLUMNS;u++){
			printf(". ");

		}
		printf("\n")
	}

	for(int n=0;n<NUM_COLUMNS;n++){
		printf("--");
	}

	for(int num=0;num<NUM_COLUMNS;num++){
		printf("%i ",num);
	}
}

