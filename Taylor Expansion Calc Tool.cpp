#include <iostream>
#include <cmath>
using namespace std;

double luythua(int n, double delta) {
	double result_lt = 1;
	if (n == 0) {
		return 1;
	}
	for (int i = 0; i < n; i++) {
		result_lt *= delta;
	}
	return result_lt;
}
double giaithua(int n) {
	double result_gt = 1;
	if (n == 0) {
		return 1;
	}
	for (int i = 0; i < n; i++) {
		result_gt *= (i + 1);
	}
	return result_gt;
}
double* solveLinearEquations(double** coefficients, double* constants, int n) {
	
	double* result = new double[n];

	
	for (int i = 0; i < n; ++i) {
		
		double pivot = coefficients[i][i];

		
		for (int j = i; j < n; ++j) {
			coefficients[i][j] /= pivot;
		}
		constants[i] /= pivot;

		
		for (int j = i + 1; j < n; ++j) {
			double factor = coefficients[j][i];
			for (int k = i; k < n; ++k) {
				coefficients[j][k] -= factor * coefficients[i][k];
			}
			constants[j] -= factor * constants[i];
		}
	}

	for (int i = n - 1; i >= 0; --i) {
		result[i] = constants[i];
		for (int j = i + 1; j < n; ++j) {
			result[i] -= coefficients[i][j] * result[j];
		}
	}

	
	cout << "Ket qua cua he phuong trinh:" << endl;
	for (int i = 0; i < n; ++i) {
		cout << "k" << i  << " = " << result[i] << endl;
	}
	return result;

	

}

void tinhdaoham() {
	int deg_accuracy,deg_derivation;
	double a, delta;
	cout << "Nhap vao so a: " << endl;
	cin >> a;
	cout << "Nhap vao delta: " << endl;
	cin >> delta;
	cout << "Nhap vao do chinh xac "<<endl;
	cin >> deg_accuracy;
	deg_accuracy += 1;
	cout << "Nhap vao bac ma ban muon dao ham: " << endl;
	cin >> deg_derivation;
	deg_derivation += 1;
	double ans[100][1];
	for (int i = 0; i < deg_accuracy; i++) {
		ans[i][0] = 0;
	}
	ans[deg_derivation-1][0] = 1;
	
	for (int i = 0; i < deg_accuracy; i++) {
		cout << "k[" << i << "]" << "\t";
	}
	cout << endl << "La cac phan tu he so cua phuong trinh: " << endl;
	cout << "f(" << deg_derivation << ")(" << a << ") = sigma_sum(k(i)f(" << a << " + i * " << delta << ")/" << delta << "+ERROR" << endl;
	double matrix[100][100];
	cout << "Ta thu duoc he phuong trinh can giai voi cac bien k[i], i chay tu 0 den " << deg_accuracy - 1 << endl;
	for (int i = 0; i < deg_accuracy; i++) {
		for (int j = 0; j < deg_accuracy; j++) {
			matrix[i][j] = 1;
		}
	}
	for (int i = 0; i < deg_accuracy; i++) {
		for (int j = 0; j < deg_accuracy; j++) {
			matrix[i][j] *= luythua(i, j);
		}
	}
	for (int i = 0; i < deg_accuracy; i++) {
		for (int j = 0; j < deg_accuracy; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << "k[" << i << "]"<<"\t"<<ans[i][0];
		cout << endl;
	}
	int n = deg_accuracy;
	double** coefficients = new double* [n];
	for (int i = 0; i < n; ++i) {
		coefficients[i] = new double[n];
	}
	double* constants = new double[n];
	for (int i = 0; i < deg_accuracy; i++) {
		for (int j = 0; j < deg_accuracy; j++) {
			coefficients[i][j] = matrix[i][j];
		}
		constants[i] = ans[i][0];
	}
	
	double* result =solveLinearEquations(coefficients, constants, n);

	double final_derivation = 0;
	double f[100];
	for (int i = 0; i < deg_accuracy; i++) {
		cout << "Nhap vao gia tri f(" << a << " + " << i << " * " << delta << "):";
		cin >> f[i];
	}
	for (int i = 0; i < deg_accuracy; i++) {
		final_derivation += result[i] * f[i];
	}
	final_derivation /= delta;
	cout << "Dao ham cap " << deg_derivation - 1 << " cua f tai x =  " << a << " la: " << final_derivation;
	for (int i = 0; i < n; ++i) {
		delete[] coefficients[i];
	}
	delete[] coefficients;
	delete[] constants;


}
void tinhvalueham() {
	int deg_accuracy;
	double a, b;
	double value_of_function=0;
	double f[100];
	cout <<"Nhap vao gia tri so a : " << endl;
	cin >> a;
	cout << "Nhap vao gia tri so b: " << endl;
	cin >> b;
	double delta = b-a;
	cout << "Delta = " << delta << endl;
	cout << "Nhap vao do chinh xac ban muon tinh, 0 la nho nhat: " << endl;
	cin >> deg_accuracy;
	while (deg_accuracy < 0) {
		cout << "Nhap sai, de nghi nhap lai: " << endl;
		cin >> deg_accuracy;
	}
	double fx = 0;
	for (int i = 0; i <deg_accuracy; i++) {
		cout << "Nhap value cua f(" << i << ")(a) - gia tri dao ham cap "<< i <<" cua ham f tai a : " << endl;
		cin >> f[i];
	}
	for (int i = 0; i < deg_accuracy; i++) {
		cout << f[i] << "\t";
	}
	cout << endl << "La he so cua ham f(i)(a) theo cac bac dao ham voi i chay tu 0 den " << deg_accuracy - 1 << endl;
	for (int i = 0; i < deg_accuracy; i++) {
		value_of_function += f[i] * luythua(i, delta) / giaithua(i);
	}
	cout << "Gia tri cua ham f(x) tai x = " << b << " la: " << value_of_function<<endl;
	cout << "Do chinh xac cua khai trien Taylor la bac: " << deg_accuracy << endl;
}

int main() {


	cout << "Nhap 1 de tinh ham tai diem chua biet: " << endl;
	cout << "Nhap 2 de tinh dao ham tai 1 diem: " << endl;
	int prog_num;
	cin >> prog_num;
	while (prog_num != 2 && prog_num != 1) {
		cout << "Nhap sai, de nghi nhap lai: " << endl;
		cin >> prog_num;
	}
	if (prog_num == 1) {
		tinhvalueham();//Do chinh xac o day se chi dung lai o 3 va 4 
	}
	if (prog_num == 2) {
		tinhdaoham();
	}
	return 0;
}