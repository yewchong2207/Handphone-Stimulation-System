#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;

class Message{
	public:
		string phoneMessage;
		Message* nextMesg;
		
		Message()
		{
			phoneMessage=" ";
		}
		
		Message(string phoneMessage)
		{
			this->phoneMessage = phoneMessage;	
		}	
};

class mesgStack{
	private:
		Message *top; 
	
	public:
		mesgStack(){
			top = NULL;
		}
		
		void sendMesg(); //push message into stack 
		void popMesg();  //pop message from stack
		
		Message* retrieveMesg(); //stack top - to get the latest message
		
		void viewLog();  //print message on screen 
		
		void printLog(); //printlist of messages in text file
		
		bool isEmpty() { //check the stack is full or not 
			return top == NULL;
		}
		
};

void mesgStack::sendMesg(){
	string newPhoneMessage;
	Message *node = new Message;
	
	if (node == NULL)
		cout << "Cannot allocate memory" << endl;
	else
	{
		system("CLS");
		cout << "<<<<<<< Send Message >>>>>>>" << endl << endl;
		
		cout << "\nContent Of Message: ";
		cin.ignore();
		getline(cin, newPhoneMessage);
		cout << endl;
		
		cout << "<< Press any key to continue >>";
		node->phoneMessage = newPhoneMessage;
		node->nextMesg = top;
		top = node;
	}
}

void mesgStack::popMesg(){
	
	Message *delNode;
	
	if (isEmpty()){
		cout << "Sorry, Cannot delete message from stack. Stack is empty!" << endl;
	}else{
		system("CLS");
		cout << "<<<<<<< Remove Message >>>>>>>" << endl << endl
	     	 << "Content of Message : " << top->phoneMessage << endl << endl;

		cout << "<< Press any key to continue >>";
		cin.get();

		delNode=top;
		top = delNode->nextMesg;
		delete(delNode);
	}
}

void mesgStack::viewLog(){
	int count = 0;
	
	Message *currNode;  // declare a pointer
	system("CLS"); // clear screen 
	cout << "<<<<<<< Display Message >>>>>>>" << endl << endl;
	currNode = top; // declare currNode to top (pointer) 
	
	while(currNode) // where there a message in stack it will run this while loop 
	{
		cout << "No " <<count+1 << endl; // display teh number of the message 
		cout << "Content of Message : "<<currNode->phoneMessage << endl<<endl; // display the message on screen
		currNode = currNode->nextMesg; // set the pointer to the next message so that later when the loop is running
		                               // it will display the next message
		count++;
	}
	
	cout << "<< Press any key to continue >>";
	cin.get();
}


void mesgStack::printLog(){
	int count = 0;
	fstream outfile("log.txt", ios::out); //open text file to output value into it
	
	if(isEmpty()){ // check whether the stack is empty 
		cout << "There is no messages yet. No file is form";
	}
	else {
		Message *currNode;
		system("CLS");
		outfile << "<<<<<<< Message >>>>>>>" << endl << endl;
		currNode = top;
		while(currNode) // where there a message in stack it will run this while loop 
		{
			outfile << "No " <<count << endl; // display teh number of the message 
			outfile << "Content of Message : "<<currNode->phoneMessage << endl<<endl; // output the message in the text file
			currNode = currNode->nextMesg; // set the pointer to the next message so that later when the loop is running
		                                  // it will display the next message
			
			count++; 
		}
	
		outfile.close(); //close file 
		cout << "The record already printed in log.txt. Check it out!"<<endl; 
	}
	
	getch();
}

Message* mesgStack::retrieveMesg(){
	if(isEmpty()){ //check whether the stack is empty 
		cout << "There are no message sent.";
	}
	else 
	{	
		return top; // return the latest message 
	}

	
}

class Contact{
	public:
		string name;
		string phoneNum;
		Contact* nextCont;
		mesgStack messages;
		
		void messageFunc();
};

void Contact::messageFunc(){ //menu for messages function
	char choice;
message:
	int cond = 1;
	
	system("CLS"); // clear screen 
	//menu for message
	cout << endl << endl; 
	cout << "  ***     ***  *******  ***    **  **    **" << endl
		 << "  ** ** ** **  **       ** **  **  **    **" << endl
		 << "  **  ***  **  *******  **  ** **  **    **" << endl
		 << "  **       **  **       **   ****  ***  ***" << endl
		 << "  **       **  *******  **    ***   ****** " << endl;
	
	for(int i = 0 ;i<50;i++){
		cout<<"-";
	}
	
	cout << "\n\t1. Send message" 
		 << "\n\t2. Delete message" 
		 << "\n\t3. Retrieve message" 
		 << "\n\t4. View log" 
		 << "\n\t5. Print log" 
		 << "\n\t6. Exit" << endl;	
	cout << "Choice:";
	cin >> choice;
	Message* msg;
	
	
	switch(choice){
		case '1': messages.sendMesg();
				 getch();
				 break;
		case '2': messages.popMesg();
				 getch();
				 break;
		case '3': msg = messages.retrieveMesg();
				  system("cls");
				  cout << "\n<<<<<<< Latest Message >>>>>>>\n" << endl;
				  cout << msg->phoneMessage << endl;
				  cout << "\n<<Press Any Key to Continue>>";
				 getch();
				 break;
		case '4': messages.viewLog();
				 getch();
				 break;
		case '5': messages.printLog();
				 getch();
				 break;
		case '6': cond=0;
				 break;
	}
	
	if(cond){
		goto message;
	}
}

class ContList{
	private:
		Contact* head;
		
	public:
		ContList() {head = NULL;}
		
		void addContact();	//add new contact
		int list();		//list out the contact(name only)
		void listContact(); //list out the contact (name + contact number)
		void editContact(); //edit contact detail
		void deleteContact(); //delete the selected contact
		void sortContact(); //sort the contact
		
		void viewContact(); //view the detail of a contact
		Contact* searchContact(); //search contact by name
		
		bool isEmpty() {return head == NULL;}
};

void ContList::addContact(){
	int currIndex = 0;
	Contact *newNode = new Contact;
	
	cout << "\nContact Name: ";
	getline(cin, newNode->name); //input name of new contact
	
	cout << "Contact Number(without '-'): ";
	cin >> newNode->phoneNum; //input phone number of new contact
	
	Contact *currNode = head;
	Contact *prevNode = NULL;
	
	//add new contact to correct position based on the alphabest of contact name
	while (currNode && newNode->name > currNode->name){
		prevNode = currNode;
		currNode = currNode->nextCont;
		currIndex++;
	}
	
	if (currIndex == 0){
		newNode->nextCont = head;
		head = newNode;
	}else{
		newNode->nextCont = prevNode->nextCont;
		prevNode->nextCont = newNode;
	}
}

int ContList::list(){
	cout << "Contact List\n";
	int currIndex = 1;
	
	Contact *currNode = head;
	
	//list out the contact (name only)
	while (currNode){
		cout << currIndex << ". Name: " << currNode->name << endl;
		currNode = currNode->nextCont;
		currIndex++;
	}
	cout << endl;
	
	return currIndex;
}

void ContList::listContact(){
	cout << "Contact List\n";
	int currIndex = 1;
	
	Contact *currNode = head;
	
	//list out the contact (name + phone number)
	while (currNode){
		cout << currIndex << ". Name: " << currNode->name << "\tContact Number: " << currNode->phoneNum << endl;
		currNode = currNode->nextCont;
		currIndex++;
	}

	cout << endl;
}

void ContList::editContact(){
	int max = list();
	
	int num;
	cout << "Select a name by specifying the number: ";
	cin >> num;
	
	if (num > max){
		cout << "This name is unavailable. Sorry!";
		return;
	}
	
	Contact *currNode = head;
	int currIndex = 1;
	
	while (currNode){
		
		//edit the contact 
		if (num == currIndex){
			string newN, newP;
			
			cin.ignore();
			cout << "Enter the new name: ";
			getline(cin, newN);
			
			cout << "Enter the new phone number: ";
			getline(cin, newP);
			
			currNode->name = newN;
			currNode->phoneNum = newP;
			
			break;
		} 
		currNode = currNode->nextCont;
		currIndex++;
	}	
	
	sortContact();
}

void ContList::deleteContact(){
	int max = list();
	
	int num;
	cout << "Please select a name by specifying the number: "; //type the list number of the contact which the user would like to delete
	cin >> num;
	
	if (num > max){
		cout << "This name is unavailable. Sorry!";
		return;
	}
	
	Contact *currNode = head;
	Contact *prevNode = NULL;
	int currIndex = 1;
	
	while (currNode){
		if (num == currIndex){
			bool ans;
			
			cout << "Are you sure you want to delete this contact? [0-No, 1-Yes]  "; //confirmation before delete the contact
			cin >> ans;
			
			if (ans){
				if (currIndex == 1){
					Contact *delNode = new Contact;
					delNode = currNode;
					head = currNode->nextCont;
					delete delNode;	
								
				}else{
					Contact *delNode = new Contact;
					delNode = currNode;
					prevNode->nextCont = currNode->nextCont;
					delete delNode;
				}
				
			}else{
				break;
			}
			
			break;
		} 
		prevNode = currNode;
		currNode = currNode->nextCont;
		currIndex++;
	}	
}

void ContList::sortContact(){ //sort contact based on alphabetical order
	Contact *current = head, *index = NULL;  
    string temp;  
          
    if(head == NULL) {  
        return;  
    }  
    else {  
        while(current != NULL) {  
            //Node index will point to node next to current  
            index = current->nextCont;  
                  
            while(index != NULL) {  
                //If current node's data is greater than index's node data, swap the data between them  
                if(current->name > index->name) {  
                    temp = current->name;  
                    current->name = index->name;  
                    index->name = temp;  
                }  
                index = index->nextCont;  
            }  
            current = current->nextCont;  
        }      
    }  
}

void ContList::viewContact(){
	int max = list();
	
	int num;
	cout << "Select a name by specifying the number: ";  //type the list number of the contact which the user would like to view
	cin >> num;
	
	if (num > max){
		cout << "This name is unavailable. Sorry!";
		return;
	}
	
	Contact *currNode = head;
	int currIndex = 1;
	
	while (currNode){
		if (num == currIndex){
			cout << "\nNAME    : " << currNode->name << endl; //display name
			cout << "Phone No: " << currNode->phoneNum << endl; //display phone number
			
			break;
		} 
		currNode = currNode->nextCont;
		currIndex++;
	}	
} 

Contact* ContList::searchContact(){
	int max = list();
	
	string name;
	cout << "Enter the name: "; //enter the name of the contact he is looking for
	cin.ignore();
	getline(cin, name);
	
	for(auto& c : name) //convert the name that user enteres to small letter
   		c = tolower(c);
	
	Contact *currNode = head;
	int currIndex = 1;
	
	while (currNode){
		string temp = currNode->name;
		
		for(auto& c : temp)//convert the name to small letter
   			c = tolower(c);	
			
		if (name == temp){
			//do comparison. If yes, return something
			cout << endl;
			cout << "NAME: " << currNode->name << endl;
			cout << "CONTACT NUMBER: " << currNode->phoneNum << endl;
			return currNode;
		} 
		 
		currNode = currNode->nextCont;
		currIndex++;
	}
	
	cout << "This name is unavailable. Sorry!";
	return NULL;
}

int main(){
	ContList list;
	cout << endl<<endl;
	// the homepage 
	cout << "\t\t##    ##  ######  ###    ## ######      ######## ##    ##  #######  ###    ## #######"<<endl;
	cout << "\t\t##    ## ##    ## ## ##  ## ##    ##    ##    ## ##    ## ##     ## ## ##  ## ##     "<<endl;
	cout << "\t\t######## ######## ##  ## ## ##    ##    ######## ######## ##     ## ##  ## ## #######"<<endl;
	cout << "\t\t##    ## ##    ## ##   #### ##    ##    ##       ##    ## ##     ## ##    ### ##     "<<endl;
	cout << "\t\t##    ## ##    ## ##    ### ######      ##       ##    ##  #######  ##    ### #######"<<endl;
	cout << endl;
	cout << "    ######## ######## ######## ###       ### ##    ## ##        ######  ######## ########  #######  ###    ##"<<endl;
	cout << "    ##          ##       ##    ## ##   ## ## ##    ## ##       ##    ##    ##       ##    ##     ## ## ##  ##"<<endl;
	cout << "    ########    ##       ##    ##  ## ##  ## ##    ## ##       ########    ##       ##    ##     ## ##  ## ##"<<endl;
	cout << "          ##    ##       ##    ##   ###   ## ##    ## ##       ##    ##    ##       ##    ##     ## ##   ####"<<endl;
	cout << "    ########    ##    ######## ##         ## ######## ######## ##    ##    ##    ########  #######  ##    ###"<<endl;
	cout << endl<<endl;
	cout << "\t\t\t######## ##    ## ######## ##    ## ######## ####### ###       ###"<<endl;
	cout << "\t\t\t##        ##  ##  ##        ##  ##     ##    ##      ## ##   ## ##"<<endl;
	cout << "\t\t\t########   ####   ########   ####      ##    ####### ##  ## ##  ##"<<endl;
	cout << "\t\t\t      ##    ##          ##    ##       ##    ##      ##   ###   ##"<<endl;
	cout << "\t\t\t########    ##    ########    ##       ##    ####### ##         ##"<<endl;
	
	cout << endl ;
	cout << "\t\t\t\t WELCOME to Hand Phone Stimulation System."<< endl; 
	cout << " ==================================================================================================================== " << endl; 
	cout << "\n Features : \n";
	cout << " * Add Contact"; 
	cout << " * View Contact"; 
	cout << " * Search Contact"; 
	cout << " * Edit Contact"; 
	cout << " * Delete Contact\n"; 
	cout << " * Send Message"; 
	cout << " * Delete Message";
	cout << " * Retrieve Message";
	cout << " * View Log";
	cout << " * Print Log in text file\n\n" ;
	cout << " =================================================================================================================== " << endl; 
	cout << endl << right << setw(116);
	cout << " Press <ENTER> to enter the system ->";
	getch();
	system("cls");

begin:	
	int choice;
	// menu for contact 
	cout << endl << endl; 
	cout << "  ***     ***  *******  ***    **  **    **" << endl
		 << "  ** ** ** **  **       ** **  **  **    **" << endl
		 << "  **  ***  **  *******  **  ** **  **    **" << endl
		 << "  **       **  **       **   ****  ***  ***" << endl
		 << "  **       **  *******  **    ***   ****** " << endl;
	
		
	for(int i = 0 ;i<50;i++){
		cout<<"-";
	}
	cout << endl;
	cout << "1. Add Contact" << endl;
	cout << "2. View Contact" << endl;
	cout << "3. Search Contact" << endl;
	cout << "4. Edit Contact" << endl;
	cout << "5. Delete Contact" << endl;
	cout << "6. Send Message & Other featuress" << endl;
	cout << "7. Exit" << endl;
	cout << "CHOICE: "; cin >> choice;
	system("cls");
	
	switch(choice){
		case 1:{
			char number;
c:
			cout << "\n<<<<<<< Add Contact >>>>>>>" << endl;
			cout << "\nNumber of contact you want to add: ";
			cin >> number;
			cout << endl;
			
			if (!isdigit(number))
				goto c;
			
			for (int i=0; i<(number-'0'); i++){
				cin.ignore();
				list.addContact();
			}
			cout << endl;
			cout << "<<Press Any Key to Continue>>";
			getch();
			system("CLS");
			goto begin;
			break;
		}
		
		case 2:{
			cout << endl;
			cout << "\n<<<<<<< View Contact >>>>>>>\n" << endl;
			list.viewContact();
			cout << endl;
			cout << "<<Press Any Key to Continue>>";
			getch();
			system("CLS");
			goto begin;
			break;
		}
		
		case 3:{
			cout << endl;
			cout << "\n<<<<<<< Search Contact >>>>>>>" << endl;
			if(list.searchContact()){
				cout << "FOUND!" << endl;
			}
			cout << endl;
			cout << "<<Press Any Key to Continue>>";
			getch();
			system("CLS");
			goto begin;
			break;
		}
		
		case 4:{
			cout << endl;
			cout << "\n<<<<<<< Edit Contact >>>>>>>" << endl;
			list.editContact();
			cout << endl;
			cout << "<<Press Any Key to Continue>>";
			getch();
			system("CLS");
			goto begin;			
			break;
		}
		
		case 5:{
			cout << endl;
			cout << "\n<<<<<<< Delete Contact >>>>>>>" << endl;
			list.deleteContact();
			cout << endl;
			cout << "<<Press Any Key to Continue>>";
			getch();
			system("CLS");
			goto begin;			
			break;
		}
		
		case 6:{
			cout << endl;
			cout << "\n<<<<<<< Send message and Other features >>>>>>>" << endl;
			Contact *curr = list.searchContact();
			if(curr != NULL){
				curr->messageFunc();
				getch();
				system("CLS");		
				goto begin;	
				break;
			}else {
				system("CLS");
				goto begin;
			}
			break;
		}
		
		default:{ // when the user enter 7 or other value , the system will disply the below information and terminate 
		cout << "\nBrought To You By UTM Data Engineering Students"<<endl; 
		cout << "Group 6:\n";
		cout << "1. Lee Sze Yuan \t(A19EC0068)"<<endl;
		cout << "2. Chia Wei Hong \t(A19EC0033)"<<endl;
		cout << "3. Loh Yew Chong \t(A19EC0076)"<<endl;
		break;

		}
	}
	
	return 0;
}
