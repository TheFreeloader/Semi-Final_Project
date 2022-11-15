#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// Given Variables
#define T_to_casher 0.5
#define T_scanItems 0.5
#define T_toPack 0.5
#define pack_box 10
#define pack_bag 5
#define pay_byCard 15
#define exact 15
#define notExact 20
#define receipt_print 0.3
#define text_data 2
#define idleTime 3


int main()
{
    ifstream fin;
    fin.open("SFinal.txt");
    if(!fin.is_open())
    {
        cout<<"Cannot Open File"<<endl;
        exit(1);
    }
    //user input variables
    int num_cust;             //number of customer
    int cart_items[10];       //number of cart items
    string pack_choice[10];   //packing method
    int number_pack[10];      //number of bags/boxs
    string pay_method[10];   //paying method
    string cash_value[10];   //cash value either exact or not exact

    //formula variables
    float Tdecart_Time=0.00;   //total decarting time
    float Tscan_Time=0.00;     //total scan time
    float Tpack_Time=0.00;     //total packing time
    float Tpaying_Time=0.00;   // total paying time
    float Tprint_Time=0.00;    //total printing time
    float T_idleTime=0.00;     // total idle time
    float Total_Queue_time=0.00; //total queue time
    float Ftotal_Queue_time=0.00;// total lane time



    //take input from user on how many customers are in the queue
    fin>>num_cust;

    //loop used to display the 3 customers
    for(int i=1;i<=num_cust;i++)
    {
        fin>>cart_items[i]>>pack_choice[i]>>number_pack[i]>>pay_method[i];
        {
            if(pay_method[i]=="cash")
            {
                fin>>cash_value[i];
            }
        }
    }

    for(int i=1;i<=num_cust;i++)
    {
        // print out the reciept
        cout<<"======================================="<<endl;
        cout<<"------Customer Number:"<<i<<"------"<<endl;
        cout<<"Number of Cart Items: "<<cart_items[i]<<endl;
        if(pack_choice[i]=="box")
        {
            cout<<"Preferred Packaging: Box"<<endl;
            cout<<"Number of Boxes:"<<number_pack[i]<<endl;
        }
        if(pack_choice[i]=="bag")
        {
            cout<<"Preferred Packaging: Bag"<<endl;
            cout<<"Number of Bags:"<<number_pack[i]<<endl;
        }
        if(pay_method[i]=="cash")
        {
            if(cash_value[i]=="e")
            {
                cout<<"Preferred Method: Cash(Exact)"<<endl;    
            }
            if(cash_value[i]=="ne")
            {
                cout<<"Preferred Method: Cash(Not Exact)"<<endl;
            }
        }
        if(pay_method[i]=="digital")
        {
            cout<<"Preferred Payment Method: Digital"<<endl;
        }
        //formulas

        Tdecart_Time = cart_items[i] * T_to_casher;
        Tscan_Time = cart_items[i] * T_scanItems;

        if(pack_choice[i]=="bag")
        {
            Tpack_Time = (cart_items[i] * T_toPack) + (number_pack[i] * pack_bag);
        }

        if(pack_choice[i]=="box")
        {
            Tpack_Time = (cart_items[i] * T_toPack) + (number_pack[i] * pack_box); 
        }
        if(pay_method[i]=="cash")
        {
            if(cash_value[i]=="e")
            {
                Tpaying_Time = exact;
            }
            if(cash_value[i]=="ne")
            {
                Tpaying_Time = notExact;
            }
        }
        if(pay_method[i]=="digital")
        {
            Tpaying_Time = pay_byCard;
        }

        Tprint_Time = (cart_items[i] * receipt_print) + text_data;

        if(i<2)
        {
            T_idleTime = idleTime - 3;  
        }
        else
        {
            T_idleTime = idleTime;
        }

        Total_Queue_time = Tdecart_Time + Tscan_Time + Tpack_Time + Tpaying_Time + Tprint_Time + T_idleTime;

        cout<<"_______________________________________"<<endl;
        cout<<"Total De-carting Time:       "<<Tdecart_Time<<endl;
        cout<<"Total Scanning Time:         "<<Tscan_Time<<endl;
        cout<<"Total Packing Time:          "<<Tpack_Time<<endl;
        cout<<"Total Paying Time:           "<<Tpaying_Time<<endl;
        cout<<"Total Receipt Printing Time: "<<Tprint_Time<<endl;
        cout<<"Idle Time:                   "<<T_idleTime<<endl;
        cout<<"Total Customer Queue Time:   "<<Total_Queue_time<<endl;
        cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
        Ftotal_Queue_time+=Total_Queue_time;
    }
    cout<<"Total Lane Queue Time: "<<Ftotal_Queue_time<<endl;
    fin.close();

    return 0;
}
