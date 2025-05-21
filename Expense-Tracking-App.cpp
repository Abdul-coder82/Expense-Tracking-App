#include <iostream>
using namespace std;

class ExpenseNode {
public:
    int expense_id;
    string productName;
    float price;
    string date;
    ExpenseNode* next;

    static int id_counter; // shared among all instances

    ExpenseNode(string name, float p, string d) {
        expense_id = ++id_counter;  // unique ID
        productName = name;
        price = p;
        date = d;
        next = NULL;
    }
};

// Initialize the static counter
int ExpenseNode::id_counter = 0;


class MasterNode {
public:
    ExpenseNode* expenseHead;
    MasterNode* next;

    MasterNode(ExpenseNode* head) 
	{
        expenseHead = head;
        next = NULL;
    }
};

// Global pointer to Master Linked List
MasterNode* masterHead = NULL;

		void addNewExpense(string name, float price, string date) 
		{
		    
		    ExpenseNode* newExpense = new ExpenseNode(name, price, date);
		
		    MasterNode* newMasterNode = new MasterNode(newExpense);
		    
		    if (masterHead == NULL) {
		        masterHead = newMasterNode;
		    } else {
		        MasterNode* temp = masterHead;
		        while (temp->next != NULL) {
		            temp = temp->next;
		        }
		        temp->next = newMasterNode;
		    }
		
		    cout << "Expense Added Successfully!\n\n";
		}

		void displayAllExpenses() 
		{
		    MasterNode* mptr = masterHead;
		    if(mptr==NULL)
		    {
		    	cout<<"No Records Exist!"<<endl;
		    	return;
			}
		    while (mptr != NULL) 
			{
		        ExpenseNode* eptr = mptr->expenseHead;
		        cout << "\nExpense ID: " << eptr->expense_id << endl;
		        cout << "Product Name: " << eptr->productName << endl;
		        cout << "Price: " << eptr->price << endl;
		        cout << "Date: " << eptr->date << endl;
		        cout << "-------------------------" << endl;
				mptr = mptr->next;
		    }
		}

		void editExpense(MasterNode* masterHead, int expenseID) 
		{
			MasterNode* mptr = masterHead;
		    ExpenseNode* current=NULL;
			while (mptr != NULL ) 
			{
				current=mptr->expenseHead;
				
				if(current!=NULL && current->expense_id==expenseID)
				{
					cout <<	"Expense ID: "<<current->expense_id<<endl;
				    cout << "Current Product Name: " <<current->productName<< endl;
				    cout << "Current Price: " <<current->price<< endl;
				    cout << "Current Date: " <<current->date<< endl;
				    // Ask user for new values
				    string newName, newDate;
				    float newPrice;
					cout << "Enter new Product Name: ";
				    cin >> newName;
				    cout << "Enter new Price: ";
				    cin >> newPrice;
				    cout << "Enter new Date [dd/mm/yy]: ";
				    cin >> newDate;
				
				    // Update values
					current->productName=newName;
					current->price=newPrice;
					current->date=newDate;
				    cout << "Expense Updated Successfully!" << endl; 
				    return;
				}
				mptr=mptr->next;
		    }
		    cout << "Expense with ID " << expenseID << " not found." << endl;
		}
		void deleteExpense(MasterNode*& masterHead, int expenseID) 
		{
		    MasterNode* mptr = masterHead;
		    MasterNode* prev = NULL;
		
		    while (mptr != NULL) 
			{
		        ExpenseNode* current = mptr->expenseHead;
		
		        if (current != NULL && current->expense_id == expenseID) 
				{
		            // Found the expense
		            cout << "Expense Details:\n";
		            cout << "Product Name: " << current->productName << endl;
		            cout << "Price: " << current->price << endl;
		            cout << "Date: " << current->date << endl;
		
		            cout << "Do you want to delete it? [y/n]: ";
		            char confirm;
		            cin >> confirm;
		
		            if (confirm == 'y') 
					{
		                // Case 1: First node in master list
		                if (prev == NULL) 
						{
		                    masterHead = mptr->next;
		                } else 
						{
		                    prev->next = mptr->next;
		                }
		
		                delete current;
		                delete mptr;
		
		                cout << "Expense Deleted Successfully!" << endl;
		                return;
		            } else 
					{
		                cout << "Okay!" << endl;
		                return;
		            }
		        }
		
		        prev = mptr;
		        mptr = mptr->next;
		    }
		
		    cout << "Expense with ID " << expenseID << " not found." << endl;
		}
		void Generalreport() 
		{
		    MasterNode* mptr = masterHead;
		    if(mptr==NULL)
		    {
		    	cout<<"No Records Exist!"<<endl;
		    	return;
			}
			float total_amount=0;
			int count=0;
			cout<<"\n----- Report -----\n";
			cout <<"\nID\t\t"<<"NAME\t\t"<<"PRICE\t\t"<<"DATE\n";
		    while (mptr != NULL) 
			{
		        ExpenseNode* eptr = mptr->expenseHead;
		        cout <<eptr->expense_id <<"\t\t";
		        cout <<eptr->productName <<"\t\t";
		        cout <<eptr->price <<"\t\t";
		        cout << eptr->date <<endl;
		        total_amount+=eptr->price;
		        count++;
				mptr = mptr->next;
		    }
		    cout<<"\nTotal Number of Expenses: "<<count<<endl;
		    cout<<"Total Amount Spent: "<<total_amount<<" PKR"<<endl;
		}
		void HighestExpense() 
		{
		    MasterNode* mptr = masterHead;
		    if (mptr == NULL) 
			{
		        cout << "No Records Exist!" << endl;
		        return;
		    }
			ExpenseNode* max = mptr->expenseHead;
		    mptr = mptr->next;
		    while (mptr != NULL) 
			{
		        ExpenseNode* eptr = mptr->expenseHead;
		        if (eptr != NULL && eptr->price > max->price) 
				{
		            max = eptr;
		        }
				mptr = mptr->next;
		    }
			cout<<"\n----- Report -----\n";
		    cout << "\nHighest Expense: " << max->productName << " - " << max->price << " PKR (" << max->date << ")" << endl;
		}
		void LowestExpense() 
		{
		    MasterNode* mptr = masterHead;
		    if (mptr == NULL) 
			{
		        cout << "No Records Exist!" << endl;
		        return;
		    }
		
		    ExpenseNode* min = mptr->expenseHead;
		    mptr = mptr->next;
		
		    while (mptr != NULL) 
			{
		        ExpenseNode* eptr = mptr->expenseHead;
		
		        if (eptr != NULL && eptr->price < min->price) 
				{
		            min = eptr;
		        }
				mptr = mptr->next;
		    }
			cout<<"\n----- Report -----\n";
		    cout << "\nLowest Expense: " << min->productName << " - " << min->price << " PKR (" << min->date << ")" << endl;
		}
		void filterByDate(string targetDate) 
		{
		    MasterNode* mptr = masterHead;
		    bool found = false;
		    cout<<"\n----- Report -----\n";
			cout <<"\nID\t\t"<<"NAME\t\t"<<"PRICE\t\t"<<"DATE\n";
		    while (mptr != NULL) 
			{
		        ExpenseNode* eptr = mptr->expenseHead;
		        if (eptr->date == targetDate) 
				{
		            cout <<eptr->expense_id <<"\t\t";
		            cout <<eptr->productName <<"\t\t";
		            cout <<eptr->price <<"\t\t";
		            cout << eptr->date <<endl;
		            found = true;
		        }
		        mptr = mptr->next;
		    }
		
		    if (!found)
		        cout << "No expense found on this date." << endl;
		}  
		void monthlyReport(string targetMonth) 
		{
		    MasterNode* mptr = masterHead;
		    float total = 0;
		    bool found = false;
			cout<<"\n----- Report -----\n";
			cout <<"\nID\t\t"<<"NAME\t\t"<<"PRICE\t\t"<<"DATE\n";
		    while (mptr != NULL) 
			{
		        ExpenseNode* eptr = mptr->expenseHead;
		
		        // Extract year-month from full date
		        string yearMonth = eptr->date.substr(3 , 9);
		
		        if (yearMonth == targetMonth) 
				{
		            cout <<eptr->expense_id <<"\t\t";
		            cout <<eptr->productName <<"\t\t";
		            cout <<eptr->price <<"\t\t";
		            cout << eptr->date <<endl;
		            total += eptr->price;
		            found = true;
		        }
		
		        mptr = mptr->next;
		    }
		
		    if (found)
		        cout << "\nTotal for " << targetMonth << ": " << total << " PKR" << endl;
		    else
		        cout << "No expenses found in this month." << endl;
		}	
  
		void GenerateReport()
		{
			bool flag;
			do
			{
				flag=true;
				cout<<"\n\t1.General Report"<<endl;
				cout<<"\t2.Highest Expense"<<endl;
				cout<<"\t3.Lowest Expense"<<endl;
				cout<<"\t4.Date-wise Filtering"<<endl;
				cout<<"\t5.Monthly Report"<<endl;
				cout<<"\t6.Exit"<<endl;
				int choi;
				cout<<"\nEnter Your Choice:";
				cin>>choi;
				cout<<endl;
				switch(choi)
				{
					case 1:
						Generalreport();
						break;
					case 2:
						HighestExpense();
						break;	
					case 3:
						LowestExpense();
						break;
					case 4:
						{
							string date_se;
							cout<<"Enter Date [dd/mm/yy]:";
							cin>>date_se;
							filterByDate(date_se);
							break;
						}
					case 5:
						{
							string date_se;
							cout<<"Enter Date [mm/yy]:";
							cin>>date_se;
							monthlyReport(date_se);	
							break;
						}	
					case 6:
						flag=false;
						break;
					default:
						cout<<"Invalid choice!"<<endl;		
				}
			}while(flag);
		}
int main() 
{
	bool flag;
	cout<<"---- Home Expense Tracking ----\n";
	do{
		flag=true;
		cout<<"\n** MAIN MENU **\n";
		cout<<"\n1.Add Expense"<<endl;
		cout<<"2.View All Expenses"<<endl;
		cout<<"3.Generate Report"<<endl;
		cout<<"4.Exit"<<endl;
		cout<<"Enter Your Choice:";
		int choice;
		cin>>choice;
		switch(choice){
			case 1:
				cout<<"\n\t1.Add new expense"<<endl;
				cout<<"\t2.Modify expense"<<endl;
				cout<<"\t3.Delete expense"<<endl;
				cout<<"\t4.Exit"<<endl;
				cout<<"Enter Your Choice:";
				int choice_in;
				cin>>choice_in;
				if(choice_in==1)
				{
					string pro_name,date;
					float price;
					char c;
					cout<<"Enter Product Name: ";
					cin>>pro_name;
					cout<<"Enter Price: ";
					cin>>price;
					cout<<"Enter Date [dd/mm/yy]: ";
					cin>>date;
					cout<<endl;
					addNewExpense(pro_name,price,date);
					cout<<"Want to Add more Expenses [y/n]? ";
					cin>>c;
					while(c=='y')
					{
						cout<<"Enter Product Name: ";
						cin>>pro_name;
						cout<<"Enter Price: ";
						cin>>price;
						cout<<"Enter Date [dd/mm/yy]: ";
						cin>>date;
						addNewExpense(pro_name,price,date);
						cout<<"[y/n]? ";
						cin>>c;
					}
					break;
				}
				else if(choice_in==2)
				{
					cout<<"Enter Expense ID: ";
					int key;
					cin>>key;
					editExpense(masterHead,key);
				}
				else if(choice_in==3)
				{
					cout<<"Enter Expense ID: ";
					int key;
					cin>>key;			
					deleteExpense(masterHead,key);
				}
				else if(choice_in==4)
				{
					break;
				}
				else
				{
					cout<<"Wrong choice!"<<endl;
					break;
				}
				break;
			case 2:
				displayAllExpenses(); 
				break;
			case 3:
				GenerateReport();
				break;
			case 4:
				flag=false;
				break;
			default:
				cout<<"Invalid choice!"<<endl;
		}
	}while(flag);
    return 0;
}
