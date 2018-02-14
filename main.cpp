#include <iostream>
#include<cstdlib>
#include<ctime>
#include "Header.h"
using namespace std;
const int MIN_PER_HR=60;
//gdgsdg
bool newcustomer(double x);
bool newcustomer(double x)
{
    
    return (rand() * x/RAND_MAX<1);
}
int main()
{
   srand (time(NULL));
    cout<<"Welcome to \"Bank of heather\""<<endl;
    cout<<"Please enter the simulation hour: ";
    int hour;
    cin>>hour;
    cout<<"Please enter the avarage time between customers (in minutes): ";
    int ave_time;
    cin>>ave_time;
    cout<<"Please enter the size of queue: ";
    int qs;
    cin>>qs;
    Queue line1(qs);
    Queue line2(qs);
    Item temp;
    long cyclelimit = hour*MIN_PER_HR;
    int customer=0;
    int served=0;
    int total_wait[2]{};
    int wait_time [2]{};
    int turnaways=0;
    long line_wait[2]{};
    for(int cycle = 0;cycle<cyclelimit;cycle++)
    {
        if(newcustomer(ave_time))
        {
            if(line1.isfull()&&line2.isfull())
                turnaways++;
            
            if(line2.queuecount()>line1.queuecount())
            {
                if(total_wait[0]>1)
                    turnaways++;
                else
                {
                customer++;
                temp.set(cycle);
                line1.enqueue(temp);
                total_wait[0]+=temp.ptime();
                }
            }
            else
            {
                if(total_wait[1]>1)
                    turnaways++;
                else
                {
                customer++;
                temp.set(cycle);
                line2.enqueue(temp);
                total_wait[1]+=temp.ptime();
                }
            }
            
        }
            if(wait_time[0]<=0&&!line1.isempty())
            {
                line1.dequeue(temp);
                wait_time[0]=temp.ptime();
                served++;
                line_wait[0]+=cycle-temp.when();
            }
        if(wait_time[1]<=0&&!line2.isempty())
        {
            line2.dequeue(temp);
            wait_time[1]=temp.ptime();
            served++;
            line_wait[1]+=cycle-temp.when();
        }
            if(wait_time[0]>0)
                wait_time[0]--;
        
            if(total_wait[0]>0)
            total_wait[0]--;
        
        if(wait_time[1]>0)
            wait_time[1]--;
        
        if(total_wait[1]>0)
            total_wait[1]--;
        
        
    }
    cout<<"Avarage number of customer per hour that wait in line less than 1 minute is: "<<served/hour<<endl;
    cout<<"Turnaway: "<<turnaways<<endl;
    return 0;
}


