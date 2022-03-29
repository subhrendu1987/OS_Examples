//Simulation of Round-Robin Scheduling algorithm used in Operating systems//
//Fixed time slice of 2 is used.Process queue is implemented a sLinked list//
//The program is tuned for 10 processes and Buurst times need to be entered//


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <malloc.h>

using namespace std;

struct node{
	int arrival;
	int burst;
	int burst1;
	int turnaround;
	int waiting;
	int finish;
	int name;

	struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;


int empty(){
	if (head == NULL)
		return 1;
	else
		return 0;
}

void append (struct node *temp){			
	if (head == NULL){
		head = temp;
		tail = temp;
		temp->next=NULL;
	}else{
		tail -> next = temp;
		tail = temp;
		tail -> next = NULL;
	}
}

struct node* serve (){
	struct node *temp;
	if (!empty()){
		temp = head;
		head = head -> next;

		return temp;
	}else{
		//cout<<"Ready q is empty"<<"\n";
		temp = new(node);
		temp -> name = 0;
		return temp;
	}
}	

int main(){
	int max;

	struct node *p[10];
	struct node *exe;

	int quantum;
	int period = 0;
	int count = 0;
	int i;
	int choice;

	double totalWaiting = 0;
	double avgWaiting;
	
	cout<<"Enter number of processes:";
	cin>>max;
	
	cout<<"Enter Time Quantum value: ";
	cin>>quantum;

	cout<<"******** Please select your choice ********";
	cout<<"1.Processes with same arrival time 0\n\n";
	cout<<"2.Processes with random arrival time\n\n";
	cout<<"3.Processes arrival time given by the user\n\n";

	cout<<"Your option is (1 / 2 / 3) >>\n ";
	cin>>choice; 
	if (choice != 1 && choice != 2 && choice != 3){ 
		cout<<"Invalid option";
	}else{ 
		for (i = 0; i < max; i++){
			p[i] =new(node);
			p[i] -> turnaround = 0;
			p[i] -> waiting = 0;
			p[i] -> finish = 0;
			p[i] -> name = i + 1;
			p[i] -> next = NULL;
		}
		if (choice == 1){
			for (i = 0; i < max; i++){
				p[i] -> arrival = 0;
			}
		}

		if (choice == 2){
			p[0] -> arrival = 0;
			int base=0;
			int r;
			cout<<"P"<<1<<" arival time is "<<p[0]->arrival << "\n";
			for (i = 1; i < max; i++){
				r= (rand() % 10) * 2;
				p[i] -> arrival = base + r;
				base=base+r;
				cout<<"P"<<i+1<<" arival time is "<<p[i]->arrival << "\n";
			}
		}
		if( choice ==3){
			for (i = 0; i < max; i++){
				cout << "Enter the arrival time of the P"<< i+1 <<"   :";
				cin>>p[i] -> arrival;
			//	cout<<i<<" arival time is "p[i]->arrival << "\n";
			}
			for (i = 0; i < max; i++){
				cout<<i<<" arival time is "<<p[i]->arrival << "\n";
			}
		}

		for (i = 0; i < max; i++){
			cout<<"Enter burst time for P"<<i + 1 <<"    :";
			cin>>p[i] -> burst; 
			p[i] -> burst1 = p[i] -> burst;
		}

		cout << "\n\n"<<endl;

		cout<<"TimeB\t\tTimeE\t\tProcess\t\tArrival\t\tBurst\t\t\n\n"<<endl;

		getchar();

		if (choice == 1){
			for (i = 0; i < max; i++){
					append (p[i]);
			}
		}
		int t=0;
		while (count < max){
			if (choice ==2 || choice ==3){
				while(t < max && p[t]->arrival <= period ) {					
					append (p[t]);
					t=t+1;
				}
			}
			exe = new(node);
			exe = serve();
        //    getchar();
			if (exe -> name != 0){
				if (exe -> burst1 > quantum){
					cout <<period <<"\t\t"; 
					exe -> burst1 = exe -> burst1 - quantum;
					period = period + quantum;
					cout <<period <<"\t\t"<<exe -> name<<"\t\t"<<exe -> arrival<<"\t\t"<<exe -> burst1 << "\t\tQ"<< endl;
						append (exe); 
					getchar();
				} 
				else{
					//if (exe -> burst1 != 0){
						cout<< period<<"   ";
						period = period + exe -> burst1;
						exe -> burst1 = 0;
						exe -> finish = period;
						exe -> turnaround = exe -> finish - exe -> arrival;
						exe -> waiting = exe -> turnaround - exe -> burst;
						count ++;
						for (i = 0; i < max; i++){
							if (p[i] -> name == exe -> name){
								p[i] = exe;
							}
						}
						cout <<"\t\t"<<period<<"\t\t" <<exe -> name<<"\t\t"<< exe -> arrival<< "\t\t"<<exe -> burst1 <<"\tFinish"	<< endl;
						getchar();
					//}
				}
			} 
			else{
				period = period + 1;
			}
		}
		cout<<" \n\n\n";
		cout << "ProcessID\tArrival time\tBurst time" <<endl;
		for(i=0;i<max;i++){
			cout<<i<<"\t\t"<<p[i]->arrival<<"\t\t"<<p[i]->burst<<endl;
		}
		cout << "ProcessID\tFinish time\tTurnAround time\tWaiting time" <<endl;

		for (i = 0; i < max; i++){
			cout << p[i] -> name<<"\t\t"<< p[i] -> finish<< "\t\t" <<p[i] -> turnaround<<"\t\t" << p[i] -> waiting<<endl;
		}
		for (i = 0; i < max; i++){
			totalWaiting = totalWaiting + p[i] -> waiting;
		}
		avgWaiting = totalWaiting / max;
		cout<<"\n\n";
		cout<<"Average waiting time is  "<<avgWaiting<<"\n";
		getchar();
	} 
} 

