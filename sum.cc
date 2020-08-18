#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main(void){
    vector<vector<double>> main_list;

    // Kroger
    vector<double> kroger = {30.00, 2.28, 25, 46.09, 3.27, 13.46,
			     38.68, 10.12};
    
    vector<double> gas = {20.21, 26.21, 25.41, 23.79, 25.02, 20.00,
			  27.78, 25.00, 30.00, 25};

    vector<double> great_expressions = {29, 30, 119};
    vector<double> gwinnett_medical_center = {1132.95};
    vector<double> northside_hospital = {54.00, 45};
    vector<double> metropolitan_radio = {25.27, 22.81};
    vector<double> cardio_group = {60, 550.03, 133.80};
    vector<double> ronald_regan_medical = {5, 5, 150, 115.95, 99.74, 43.85};
    vector<double> gwinnett_derma = {60};
    vector<double> cars = {19.99};
    vector<double> thomas_eye = {168.00, 10};
    vector<double> accupunture = {650, 320};
    vector<double> health_insurance = {920.14, 520, 6592.92, 181.70, 700.00};
    vector<double> phone = {12 * 150.00};
    
    // Now sum the total:
    main_list.push_back(kroger);
    main_list.push_back(gas);
    main_list.push_back(great_expressions);
    main_list.push_back(gwinnett_medical_center);
    main_list.push_back(northside_hospital);
    main_list.push_back(metropolitan_radio);
    main_list.push_back(cardio_group);
    main_list.push_back(ronald_regan_medical);
    main_list.push_back(gwinnett_derma);
    main_list.push_back(cars);
    main_list.push_back(thomas_eye);
    main_list.push_back(accupunture);
    //
    main_list.push_back(health_insurance);
    main_list.push_back(phone);
    
    double total_sum = 0;
    double temp_sum;
    
    for (auto &i : main_list){
	temp_sum = accumulate(i.begin(), i.end(), 0.0);
	cout << "Item Sum: $" << temp_sum << endl;
	total_sum += temp_sum;
    }
    cout << "The total sum is $" << total_sum << endl;
}
