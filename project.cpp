#include <bits/stdc++.h>

using namespace std;

int main()
{
    int S[3] = {1, 5, 10};
    int Q, i, j, num, k, cos;
    int arrival_num;
    double arrival, service;
    ofstream out;
    out.open("output.txt");
    i = 0;
    // for(i=0;i<3;i++){
    num = S[i];
    out << "server_num =" << num << endl;  // server num
    // for(j=0;j<10;j++){      //runtime
    int order = 0;
    for (arrival = 0.01; arrival <= 10; arrival *= 10) {
        for (service = 0.01; service <= 10.24; service *= 4) {
            double p_a = 0, p_b = 0;  // probability
            int b = 0;                // how many is blocking
            int carri = 0;            // count arrival time
            int cdep = 0;             // count depart time
            int arri_num = 0;
            int block_num = 0;
            int depart_num = 0;
            int service_num = 0;

            for (k = 0; k < 100000; k++) {  // time unit
                Q = 0;                      // Q=0
                p_a += arrival;
                if (p_a >= 1) {
                    // cout<<"arrival !"<<k<<endl;
                    arri_num++;
                    p_a -= 1;
                    if (service_num < num) {  // if service not full
                        service_num++;
                        carri++;
                    } else if (service_num == num) {  // if service is full
                        // cout<<"service full! "<<k<<endl;
                        if (Q > 0) {
                            Q--;
                        } else {
                            block_num++;
                            b++;
                            // cout<<"blocknum "<< b<<endl; //blocking people
                        }
                    }
                }
                if (service_num > 0) {  // if service is occupied
                    p_b += service;
                    if (p_b >= 1) {
                        cdep++;
                        // cout<<"depart service "<<k<<endl;         //depart
                        // service
                        service_num--;
                        p_b -= 1;
                        if (Q > 0) {
                            Q--;
                            service_num++;
                        }
                        if (b > 0) {
                            b--;
                            Q++;
                        }
                    }
                }
            }

            out << "b_num: " << block_num << "\t arri_num  " << carri;
            out << "\tbp_" << order << " = ";
            out << (double) block_num / (double) carri << endl;
            order++;
        }
    }
    //}
    out << "================================================" << endl;
    // }
    out.close();
}
