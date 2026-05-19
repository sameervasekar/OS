#include<iostream>
using namespace std;

int main()
{
    int choice;

    cout<<"1. Paging\n2. Segmentation\n";
    cout<<"Enter your choice: ";
    cin>>choice;

    if(choice == 1)
    {
        int pageSize, pageNo, offset, frameNo;

        cout<<"Enter Page Size: ";
        cin>>pageSize;

        cout<<"Enter Page Number: ";
        cin>>pageNo;

        cout<<"Enter Offset: ";
        cin>>offset;

        cout<<"Enter Frame Number (from page table): ";
        cin>>frameNo;

        int physicalAddress = frameNo * pageSize + offset;

        cout<<"\nPhysical Address = "<<physicalAddress<<endl;
    }
    else if(choice == 2)
    {
        int base, limit, offset;

        cout<<"Enter Base Address: ";
        cin>>base;

        cout<<"Enter Limit: ";
        cin>>limit;

        cout<<"Enter Offset: ";
        cin>>offset;

        if(offset < limit)
        {
            int physicalAddress = base + offset;
            cout<<"\nPhysical Address = "<<physicalAddress<<endl;
        }
        else
        {
            cout<<"\nError: Offset exceeds limit (Segmentation Fault)\n";
        }
    }
    else
    {
        cout<<"Invalid Choice\n";
    }

    return 0;
}