#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc==0 || argc==1) cout << "Please input numbers to find average.\n"; //argc จะเท่ากับ 1 เสมอ ไม่จำเป็นต้องใส่ argc==0 ก็ได้
    else
    {
    double sum=0;
    double avg=0;
        for (int i = 1; i < argc; i++)
        {
            sum += atof(argv[i]);
        }
    avg=sum/(argc-1);
    cout << "---------------------------------\n";
    cout << "Average of " << argc-1 << " numbers = " << avg << endl;
    cout << "---------------------------------";
    }
}