/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 02/18/2020
 * 
 * Homework02_06
 * This file exists to solve Problem 6 in the homework, which involves plotting
 * points for Client-Server and P2P.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <string>
#include <new>
#include <cmath>
using namespace std;
// u_s = server upload capacity (in Mps)
// F = File size (in bits)
//d_i = Peer i download capacity (in Mps)
//u_i = Peer i upload capacity (in Mbps)
//n -- numbers of peers
double client_server_time(double u_s, double f, double d_i, double u_i, int n){
    double value1 = (n * f) / (u_s);
    double value2 = f / d_i; //d_min)
    return (value1 > value2) ? value1 : value2;
}

double p2p_time(double u_s, double f, double d_i, double u_i, int n){
    double value1 = f / u_s;
    double value2 = f / d_i;
    double value3 = (n * f) / (u_s + n * u_i);

    double result = (value1 > value2) ? value1 : value2;
    result = (value3 > result) ? value3 : result;

    return result;
}


int main(void){
    // upload is in Mbps
    double file_size = 15 * pow(10, 9);
    double server_capacity = 30 * pow(10, 6);
    double d_i = 2 * pow(10, 6);
    vector<double> upload = {.3, .7, 2};
    vector<int> peers = {10, 100, 1000};
    cout << "Printing out values for Client-Server time:" << endl;
    for (int i = 0; i < upload.size(); i++){
	cout << "Value " << i << " : "
	     << client_server_time(server_capacity, file_size,
				   d_i, (upload[i] * pow(10, 6)),
				   peers[i])
	     << " seconds\n";

    }
    

}
