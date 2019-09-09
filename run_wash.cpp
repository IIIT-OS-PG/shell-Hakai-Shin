#include "wash.h"
#include "washconfig.h"
/*
	An infinte loop which keeps taking input from the user until
	user exits the program
*/

int run_wash() {
	//cout<<"entered shell loop";
	int status;
cout<<getenv("PS1")<<":";
	while(1){
	
	status=comparse();
		//if comparse() returns 0 means no/wrong input,else comparse will do its processing
	if(status==0) {
		cout<<"Command not found\n";
		continue;
	}
		//if comparse returns 2 means input is exit
	else if(status==2)
       exit(0);
	   cout<<"\n";
	   cout<<getenv("PS1")<<":";
	}
	return 1;
}
