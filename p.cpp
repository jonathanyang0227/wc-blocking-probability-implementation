#include <bits/stdc++.h>

using namespace std;
int ramdom(double percent)
{
    if (percent >=1) {
        return percent;
    } else {
        percent *= 100;
        int n = rand() % 100;
        //cout<<n<<endl;
        if (n < percent) {
            return 1;
        } else {
            return 0;
        }
    }
}
int main()
{
    int S[3] = {1, 5, 10};
    srand(time(NULL));
    int Q, i, j, service_num, k, cos;
    int arrival_num;
    double arrival, service;
    ofstream out;
    out.open("output.txt");
    i = 0;
    cout << "Q = " ;
    cin >> Q;
    for(i=0;i<3;i++){
    service_num = S[i];
    out << "server_num =" << service_num << endl;  // server num
    // for(j=0;j<10;j++){      //runtime
    int order = 1;
    for (arrival = 0.01; arrival <= 10; arrival *= 10) {
        for (service = 0.01; service <= 10.24; service *= 4) {
            out<<"arri = "<<arrival<<"  service = "<<service<<"  ";
            int cb = 0;     // how many is blocking
            int carri = 0;  // counts of arrival time
            int cdep = 0;   // counts of depart time
            int arri_num = 0;
            int block_num = 0;
            int depart_num = 0;
            int num_in_service = 0;
            int num_in_Q = 0;
            for (k = 0; k < 1000000; k++) {  // time unit
                arri_num = ramdom(arrival);
                //cout<<arri_num<<endl;
                if (arri_num >= 1) {
                    carri += arri_num;
                    for (int h = 0; h < arri_num; h++) {
                        if (num_in_service <
                            service_num) {  // if service not full
                            num_in_service++;
                        } else if (num_in_service ==
                                   service_num) {  // if service is full
                            if (Q > num_in_Q) {
                                num_in_Q++;
                            } else if(Q==num_in_Q){
                                block_num++;
                                cb++;
                            }
                        }
                    }
                }
                if (num_in_service > 0) {  // if service is occupied
                    depart_num = ramdom(service);
                    //cout<<depart_num<<endl;
                    if (depart_num >= 1) { 
                        if(depart_num>num_in_service)
                            depart_num=num_in_service;
                        cdep += depart_num;
                        for (int h = 0; h < depart_num; h++) {
                            num_in_service--;
                            if (num_in_Q > 0) {
                                num_in_Q--;
                                num_in_service++;
                                if(block_num>0){
                                    block_num--;
                                    num_in_Q++;
                                }
                            }else if(Q==0 && block_num>0) {
                                block_num--;
                                num_in_service++;
                            }
                        }
                    }
                }
            }
            //out << "b_num: " << cb<< "\t arri_num  " << carri;
            out << "\tbp_" << order << " = ";
            out << (double) cb / (double) carri << endl;
            order++;
        }
    }
    //}
    out << "================================================" << endl;
    }
    out.close();
}
